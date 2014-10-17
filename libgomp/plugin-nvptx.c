/* Plugin for NVPTX execution.

   Copyright (C) 2013-2014 Free Software Foundation, Inc.

   Contributed by Mentor Embedded.

   This file is part of the GNU OpenMP Library (libgomp).

   Libgomp is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   Libgomp is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

/* Nvidia PTX-specific parts of OpenACC support.  The cuda driver
   library appears to hold some implicit state, but the documentation
   is not clear as to what that state might be.  Or how one might
   propagate it from one thread to another.  */

//#define DEBUG
//#define DISABLE_ASYNC

#include "openacc.h"
#include "config.h"
#include "libgomp.h"
#include "target.h"
#include "libgomp-plugin.h"

#include <cuda.h>
#include <sys/queue.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <assert.h>

#define	ARRAYSIZE(X) (sizeof (X) / sizeof ((X)[0]))

static struct _errlist
{
  CUresult r;
  char *m;
} cuErrorList[] = {
    { CUDA_ERROR_INVALID_VALUE, "invalid value" },
    { CUDA_ERROR_OUT_OF_MEMORY, "out of memory" },
    { CUDA_ERROR_NOT_INITIALIZED, "not initialized" },
    { CUDA_ERROR_DEINITIALIZED, "deinitialized" },
    { CUDA_ERROR_PROFILER_DISABLED, "profiler disabled" },
    { CUDA_ERROR_PROFILER_NOT_INITIALIZED, "profiler not initialized" },
    { CUDA_ERROR_PROFILER_ALREADY_STARTED, "already started" },
    { CUDA_ERROR_PROFILER_ALREADY_STOPPED, "already stopped" },
    { CUDA_ERROR_NO_DEVICE, "no device" },
    { CUDA_ERROR_INVALID_DEVICE, "invalid device" },
    { CUDA_ERROR_INVALID_IMAGE, "invalid image" },
    { CUDA_ERROR_INVALID_CONTEXT, "invalid context" },
    { CUDA_ERROR_CONTEXT_ALREADY_CURRENT, "context already current" },
    { CUDA_ERROR_MAP_FAILED, "map error" },
    { CUDA_ERROR_UNMAP_FAILED, "unmap error" },
    { CUDA_ERROR_ARRAY_IS_MAPPED, "array is mapped" },
    { CUDA_ERROR_ALREADY_MAPPED, "already mapped" },
    { CUDA_ERROR_NO_BINARY_FOR_GPU, "no binary for gpu" },
    { CUDA_ERROR_ALREADY_ACQUIRED, "already acquired" },
    { CUDA_ERROR_NOT_MAPPED, "not mapped" },
    { CUDA_ERROR_NOT_MAPPED_AS_ARRAY, "not mapped as array" },
    { CUDA_ERROR_NOT_MAPPED_AS_POINTER, "not mapped as pointer" },
    { CUDA_ERROR_ECC_UNCORRECTABLE, "ecc uncorrectable" },
    { CUDA_ERROR_UNSUPPORTED_LIMIT, "unsupported limit" },
    { CUDA_ERROR_CONTEXT_ALREADY_IN_USE, "context already in use" },
    { CUDA_ERROR_PEER_ACCESS_UNSUPPORTED, "peer access unsupported" },
    { CUDA_ERROR_INVALID_SOURCE, "invalid source" },
    { CUDA_ERROR_FILE_NOT_FOUND, "file not found" },
    { CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND,
                                            "shared object symbol not found" },
    { CUDA_ERROR_SHARED_OBJECT_INIT_FAILED, "shared object init error" },
    { CUDA_ERROR_OPERATING_SYSTEM, "operating system" },
    { CUDA_ERROR_INVALID_HANDLE, "invalid handle" },
    { CUDA_ERROR_NOT_FOUND, "not found" },
    { CUDA_ERROR_NOT_READY, "not ready" },
    { CUDA_ERROR_LAUNCH_FAILED, "launch error" },
    { CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES, "launch out of resources" },
    { CUDA_ERROR_LAUNCH_TIMEOUT, "launch timeout" },
    { CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING,
                                            "launch incompatibe texturing" },
    { CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED, "peer access already enabled" },
    { CUDA_ERROR_PEER_ACCESS_NOT_ENABLED, "peer access not enabled " },
    { CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE, "primary cotext active" },
    { CUDA_ERROR_CONTEXT_IS_DESTROYED, "context is destroyed" },
    { CUDA_ERROR_ASSERT, "assert" },
    { CUDA_ERROR_TOO_MANY_PEERS, "too many peers" },
    { CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED,
                                            "host memory already registered" },
    { CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED, "host memory not registered" },
    { CUDA_ERROR_NOT_PERMITTED, "no permitted" },
    { CUDA_ERROR_NOT_SUPPORTED, "not supported" },
    { CUDA_ERROR_UNKNOWN, "unknown" }
};

static char errmsg[128];

static char *
cuErrorMsg (CUresult r)
{
  int i;

  for (i = 0; i < ARRAYSIZE (cuErrorList); i++)
    {
      if (cuErrorList[i].r == r)
	return &cuErrorList[i].m[0];
    }

  sprintf (&errmsg[0], "unknown result code: %5d", r);

  return &errmsg[0];
}

struct targ_fn_descriptor
{
  CUfunction fn;
  const char *name;
};

static bool PTX_inited = false;

struct PTX_stream
{
  CUstream stream;
  pthread_t host_thread;
  bool multithreaded;

  CUdeviceptr d;
  void *h;
  void *h_begin;
  void *h_end;
  void *h_next;
  void *h_prev;
  void *h_tail;

  SLIST_ENTRY(PTX_stream) next;
};

SLIST_HEAD(PTX_streams, PTX_stream);

/* Each thread may select a stream (also specific to a device/context).  */
static __thread struct PTX_stream *current_stream;

struct map
{
  int     async;
  size_t  size;
  char    mappings[0];
};

static void
map_init (struct PTX_stream *s)
{
  CUresult r;

  int size = getpagesize ();

  assert (s);
  assert (!s->d);
  assert (!s->h);

  r = cuMemAllocHost (&s->h, size);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuMemAllocHost error: %s", cuErrorMsg (r));

  r = cuMemHostGetDevicePointer (&s->d, s->h, 0);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuMemHostGetDevicePointer error: %s", cuErrorMsg (r));

  assert (s->h);

  s->h_begin = s->h;
  s->h_end = s->h_begin + size;
  s->h_next = s->h_prev = s->h_tail = s->h_begin;

  assert (s->h_next);
  assert (s->h_end);
}

static void
map_fini (struct PTX_stream *s)
{
  CUresult r;
  
  r = cuMemFreeHost (s->h);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuMemFreeHost error: %s", cuErrorMsg (r));
}

static void
map_pop (struct PTX_stream *s)
{
  struct map *m;

  assert (s != NULL);
  assert (s->h_next);
  assert (s->h_prev);
  assert (s->h_tail);

  m = s->h_tail;

  s->h_tail += m->size;

  if (s->h_tail >= s->h_end)
    s->h_tail = s->h_begin + (int) (s->h_tail - s->h_end);

  if (s->h_next == s->h_tail)
    s->h_prev = s->h_next;

  assert (s->h_next >= s->h_begin);
  assert (s->h_tail >= s->h_begin);
  assert (s->h_prev >= s->h_begin);

  assert (s->h_next <= s->h_end);
  assert (s->h_tail <= s->h_end);
  assert (s->h_prev <= s->h_end);
}

static void
map_push (struct PTX_stream *s, int async, size_t size, void **h, void **d)
{
  int left;
  int offset;
  struct map *m;

  assert (s != NULL);

  left = s->h_end - s->h_next;
  size += sizeof (struct map);

  assert (s->h_prev);
  assert (s->h_next);

  if (size >= left)
    {
      m = s->h_prev;
      m->size += left;
      s->h_next = s->h_begin;

      if (s->h_next + size > s->h_end)
	gomp_plugin_fatal ("unable to push map");
    }

  assert (s->h_next);

  m = s->h_next;
  m->async = async;
  m->size = size;

  offset = (void *)&m->mappings[0] - s->h;

  *d = (void *)(s->d + offset);
  *h = (void *)(s->h + offset);

  s->h_prev = s->h_next;
  s->h_next += size;

  assert (s->h_prev);
  assert (s->h_next);

  assert (s->h_next >= s->h_begin);
  assert (s->h_tail >= s->h_begin);
  assert (s->h_prev >= s->h_begin);
  assert (s->h_next <= s->h_end);
  assert (s->h_tail <= s->h_end);
  assert (s->h_prev <= s->h_end);

  return;
}

struct PTX_device
{
  CUcontext ctx;
  bool ctx_shared;
  CUdevice dev;
  struct PTX_stream *null_stream;
  /* All non-null streams associated with this device (actually context),
     either created implicitly or passed in from the user (via
     acc_set_cuda_stream).  */
  struct PTX_streams active_streams;
  struct {
    struct PTX_stream **arr;
    int size;
  } async_streams;
  /* A lock for use when manipulating the above stream list and array.  */
  gomp_mutex_t stream_lock;
  int ord;
  bool overlap;
  bool map;
  bool concur;
  int  mode;
  bool mkern;
  SLIST_ENTRY(PTX_device) next;
};

static __thread struct PTX_device *PTX_dev;
static SLIST_HEAD(_PTX_devices, PTX_device) _PTX_devices;
static struct _PTX_devices *PTX_devices;

enum PTX_event_type
{
  PTX_EVT_MEM,
  PTX_EVT_KNL,
  PTX_EVT_SYNC
};

struct PTX_event
{
  CUevent *evt;
  int type;
  void *addr;
  void *tgt;
  int ord;
  SLIST_ENTRY(PTX_event) next;
};

static gomp_mutex_t PTX_event_lock;
static SLIST_HEAD(_PTX_events, PTX_event) _PTX_events;
static struct _PTX_events *PTX_events;

#define _XSTR(s) _STR(s)
#define _STR(s) #s

static struct _synames
{
  char *n;
} cuSymNames[] =
{
  { _XSTR(cuCtxCreate) },
  { _XSTR(cuCtxDestroy) },
  { _XSTR(cuCtxGetCurrent) },
  { _XSTR(cuCtxPushCurrent) },
  { _XSTR(cuCtxSynchronize) },
  { _XSTR(cuDeviceGet) },
  { _XSTR(cuDeviceGetAttribute) },
  { _XSTR(cuDeviceGetCount) },
  { _XSTR(cuEventCreate) },
  { _XSTR(cuEventDestroy) },
  { _XSTR(cuEventQuery) },
  { _XSTR(cuEventRecord) },
  { _XSTR(cuInit) },
  { _XSTR(cuLaunchKernel) },
  { _XSTR(cuLinkAddData) },
  { _XSTR(cuLinkComplete) },
  { _XSTR(cuLinkCreate) },
  { _XSTR(cuMemAlloc) },
  { _XSTR(cuMemAllocHost) },
  { _XSTR(cuMemcpy) },
  { _XSTR(cuMemcpyDtoH) },
  { _XSTR(cuMemcpyDtoHAsync) },
  { _XSTR(cuMemcpyHtoD) },
  { _XSTR(cuMemcpyHtoDAsync) },
  { _XSTR(cuMemFree) },
  { _XSTR(cuMemFreeHost) },
  { _XSTR(cuMemGetAddressRange) },
  { _XSTR(cuMemHostGetDevicePointer) },
  { _XSTR(cuMemHostRegister) },
  { _XSTR(cuMemHostUnregister) },
  { _XSTR(cuModuleGetFunction) },
  { _XSTR(cuModuleLoadData) },
  { _XSTR(cuStreamDestroy) },
  { _XSTR(cuStreamQuery) },
  { _XSTR(cuStreamSynchronize) },
  { _XSTR(cuStreamWaitEvent) }
};

static int
verify_device_library (void)
{
  int i;
  void *dh, *ds;

  dh = dlopen ("libcuda.so", RTLD_LAZY);
  if (!dh)
    return -1;

  for (i = 0; i < ARRAYSIZE (cuSymNames); i++)
    {
      ds = dlsym (dh, cuSymNames[i].n);
      if (!ds)
        return -1;
    }

  dlclose (dh);
  
  return 0;
}

static void
init_streams_for_device (struct PTX_device *ptx_dev, int concurrency)
{
  int i;
  struct PTX_stream *null_stream
    = gomp_plugin_malloc (sizeof (struct PTX_stream));

  null_stream->stream = NULL;
  null_stream->host_thread = pthread_self ();
  null_stream->multithreaded = true;
  null_stream->d = (CUdeviceptr) NULL;
  null_stream->h = NULL;
  map_init (null_stream);
  ptx_dev->null_stream = null_stream;
  
  SLIST_INIT (&ptx_dev->active_streams);
  gomp_plugin_mutex_init (&ptx_dev->stream_lock);
  
  if (concurrency < 1)
    concurrency = 1;
  
  /* This is just a guess -- make space for as many async streams as the
     current device is capable of concurrently executing.  This can grow
     later as necessary.  No streams are created yet.  */
  ptx_dev->async_streams.arr
    = gomp_plugin_malloc (concurrency * sizeof (struct PTX_stream *));
  ptx_dev->async_streams.size = concurrency;
  
  for (i = 0; i < concurrency; i++)
    ptx_dev->async_streams.arr[i] = NULL;
}

static void
fini_streams_for_device (struct PTX_device *ptx_dev)
{
  struct PTX_stream *s;
  free (ptx_dev->async_streams.arr);
  
  while (!SLIST_EMPTY (&ptx_dev->active_streams))
    {
      s = SLIST_FIRST (&ptx_dev->active_streams);
      SLIST_REMOVE_HEAD (&ptx_dev->active_streams, next);
      cuStreamDestroy (s->stream);
      map_fini (s);
      free (s);
    }
  
  map_fini (ptx_dev->null_stream);
  free (ptx_dev->null_stream);
}

/* Select a stream for (OpenACC-semantics) ASYNC argument for the current
   thread THREAD (and also current device/context).  If CREATE is true, create
   the stream if it does not exist (or use EXISTING if it is non-NULL), and
   associate the stream with the same thread argument.  Returns stream to use
   as result.  */

static struct PTX_stream *
select_stream_for_async (int async, pthread_t thread, bool create,
			 CUstream existing)
{
  /* Local copy of TLS variable.  */
  struct PTX_device *ptx_dev = PTX_dev;
  struct PTX_stream *stream = NULL;
  int orig_async = async;
  
  /* The special value acc_async_noval (-1) maps (for now) to an
     implicitly-created stream, which is then handled the same as any other
     numbered async stream.  Other options are available, e.g. using the null
     stream for anonymous async operations, or choosing an idle stream from an
     active set.  But, stick with this for now.  */
  if (async > acc_async_sync)
    async++;
  
  if (create)
    gomp_plugin_mutex_lock (&ptx_dev->stream_lock);

  /* NOTE: AFAICT there's no particular need for acc_async_sync to map to the
     null stream, and in fact better performance may be obtainable if it doesn't
     (because the null stream enforces overly-strict synchronisation with
     respect to other streams for legacy reasons, and that's probably not
     needed with OpenACC).  Maybe investigate later.  */
  if (async == acc_async_sync)
    stream = ptx_dev->null_stream;
  else if (async >= 0 && async < ptx_dev->async_streams.size
	   && ptx_dev->async_streams.arr[async] && !(create && existing))
    stream = ptx_dev->async_streams.arr[async];
  else if (async >= 0 && create)
    {
      if (async >= ptx_dev->async_streams.size)
        {
	  int i, newsize = ptx_dev->async_streams.size * 2;
	  
	  if (async >= newsize)
	    newsize = async + 1;
	  
	  ptx_dev->async_streams.arr
	    = gomp_plugin_realloc (ptx_dev->async_streams.arr,
				   newsize * sizeof (struct PTX_stream *));
	  
	  for (i = ptx_dev->async_streams.size; i < newsize; i++)
	    ptx_dev->async_streams.arr[i] = NULL;
	  
	  ptx_dev->async_streams.size = newsize;
	}

      /* Create a new stream on-demand if there isn't one already, or if we're
	 setting a particular async value to an existing (externally-provided)
	 stream.  */
      if (!ptx_dev->async_streams.arr[async] || existing)
        {
	  CUresult r;
	  struct PTX_stream *s
	    = gomp_plugin_malloc (sizeof (struct PTX_stream));

	  if (existing)
	    s->stream = existing;
	  else
	    {
	      r = cuStreamCreate (&s->stream, CU_STREAM_DEFAULT);
	      if (r != CUDA_SUCCESS)
		gomp_plugin_fatal ("cuStreamCreate error: %s", cuErrorMsg (r));
	    }
	  
	  /* If CREATE is true, we're going to be queueing some work on this
	     stream.  Associate it with the current host thread.  */
	  s->host_thread = thread;
	  s->multithreaded = false;
	  
	  s->d = (CUdeviceptr) NULL;
	  s->h = NULL;
	  map_init (s);
	  
	  SLIST_INSERT_HEAD (&ptx_dev->active_streams, s, next);
	  ptx_dev->async_streams.arr[async] = s;
	}

      stream = ptx_dev->async_streams.arr[async];
    }
  else if (async < 0)
    gomp_plugin_fatal ("bad async %d", async);

  if (create)
    {
      assert (stream != NULL);

      /* If we're trying to use the same stream from different threads
	 simultaneously, set stream->multithreaded to true.  This affects the
	 behaviour of acc_async_test_all and acc_wait_all, which are supposed to
	 only wait for asynchronous launches from the same host thread they are
	 invoked on.  If multiple threads use the same async value, we make note
	 of that here and fall back to testing/waiting for all threads in those
	 functions.  */
      if (thread != stream->host_thread)
        stream->multithreaded = true;

      gomp_plugin_mutex_unlock (&ptx_dev->stream_lock);
    }
  else if (stream && !stream->multithreaded
	   && !pthread_equal (stream->host_thread, thread))
    gomp_plugin_fatal ("async %d used on wrong thread", orig_async);

#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s using stream %p (CUDA stream %p) "
	   "for async %d\n", __FILE__, __FUNCTION__, stream,
	   stream ? stream->stream : NULL, orig_async);
#endif

  return stream;
}

static int PTX_get_num_devices (void);

/* Initialize the device.  */
static int
PTX_init (void)
{
  CUresult r;
  int rc;

  if (PTX_inited)
    return PTX_get_num_devices ();

  rc = verify_device_library ();
  if (rc < 0)
    return -1;

  r = cuInit (0);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuInit error: %s", cuErrorMsg (r));

  PTX_devices = &_PTX_devices;
  PTX_events = &_PTX_events;

  SLIST_INIT(PTX_devices);
  SLIST_INIT(PTX_events);

  gomp_plugin_mutex_init (&PTX_event_lock);

  PTX_inited = true;

  return PTX_get_num_devices ();
}

static int
PTX_fini (void)
{
  PTX_inited = false;

  return 0;
}

static void *
PTX_open_device (int n)
{
  CUdevice dev;
  CUresult r;
  int async_engines, pi;

  if (PTX_devices)
    {
      struct PTX_device *ptx_device;

      SLIST_FOREACH(ptx_device, PTX_devices, next)
        {
          if (ptx_device->ord == n)
            {
              PTX_dev = ptx_device;

              if (PTX_dev->ctx)
                {
                  r = cuCtxPushCurrent (PTX_dev->ctx);
                  if (r != CUDA_SUCCESS)
                    gomp_plugin_fatal ("cuCtxPushCurrent error: %s",
				       cuErrorMsg (r));
                }

              return (void *)PTX_dev;
            }
        }
    }

  r = cuDeviceGet (&dev, n);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuDeviceGet error: %s", cuErrorMsg (r));

  PTX_dev = gomp_plugin_malloc (sizeof (struct PTX_device));
  PTX_dev->ord = n;
  PTX_dev->dev = dev;
  PTX_dev->ctx_shared = false;

  SLIST_INSERT_HEAD(PTX_devices, PTX_dev, next);

  r = cuCtxGetCurrent (&PTX_dev->ctx);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuCtxGetCurrent error: %s", cuErrorMsg (r));

  if (!PTX_dev->ctx)
    {
      r = cuCtxCreate (&PTX_dev->ctx, CU_CTX_SCHED_AUTO, dev);
      if (r != CUDA_SUCCESS)
	gomp_plugin_fatal ("cuCtxCreate error: %s", cuErrorMsg (r));
    }
  else
    {
      PTX_dev->ctx_shared = true;
    }
   
  r = cuDeviceGetAttribute (&pi, CU_DEVICE_ATTRIBUTE_GPU_OVERLAP, dev);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuDeviceGetAttribute error: %s", cuErrorMsg (r));

  PTX_dev->overlap = pi;

  r = cuDeviceGetAttribute (&pi, CU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY, dev);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuDeviceGetAttribute error: %s", cuErrorMsg (r));

  PTX_dev->map = pi;

  r = cuDeviceGetAttribute (&pi, CU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS, dev);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuDeviceGetAttribute error: %s", cuErrorMsg (r));

  PTX_dev->concur = pi;

  r = cuDeviceGetAttribute (&pi, CU_DEVICE_ATTRIBUTE_COMPUTE_MODE, dev);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuDeviceGetAttribute error: %s", cuErrorMsg (r));

  PTX_dev->mode = pi;

  r = cuDeviceGetAttribute (&pi, CU_DEVICE_ATTRIBUTE_INTEGRATED, dev);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuDeviceGetAttribute error: %s", cuErrorMsg (r));

  PTX_dev->mkern = pi;

  r = cuDeviceGetAttribute (&async_engines,
			    CU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT, dev);
  if (r != CUDA_SUCCESS)
    async_engines = 1;

  init_streams_for_device (PTX_dev, async_engines);

  current_stream = PTX_dev->null_stream;

  return (void *)PTX_dev;
}

static int
PTX_close_device (void *h __attribute__((unused)))
{
  CUresult r;

  if (!PTX_dev)
    return 0;
  
  fini_streams_for_device (PTX_dev);

  if (!PTX_dev->ctx_shared)
    {
      r = cuCtxDestroy (PTX_dev->ctx);
      if (r != CUDA_SUCCESS)
	gomp_plugin_fatal ("cuCtxDestroy error: %s", cuErrorMsg (r));
    }

  SLIST_REMOVE(PTX_devices, PTX_dev, PTX_device, next);
  free (PTX_dev);

  PTX_dev = NULL;

  return 0;
}

static int
PTX_get_num_devices (void)
{
  int n;
  CUresult r;

  assert (PTX_inited);

  r = cuDeviceGetCount (&n);
  if (r!= CUDA_SUCCESS)
    gomp_plugin_fatal ("cuDeviceGetCount error: %s", cuErrorMsg (r));

  return n;
}

static bool
PTX_avail(void)
{
  bool avail = false;

  if (PTX_init () > 0)
    avail = true;

  return avail;
}

#define ABORT_PTX				\
  ".version 3.1\n"				\
  ".target sm_30\n"				\
  ".address_size 64\n"				\
  ".visible .func abort;\n"			\
  ".visible .func abort\n"			\
  "{\n"						\
  "trap;\n"					\
  "ret;\n"					\
  "}\n"						\
  ".visible .func _gfortran_abort;\n"		\
  ".visible .func _gfortran_abort\n"		\
  "{\n"						\
  "trap;\n"					\
  "ret;\n"					\
  "}\n" \

/* Generated with:

   $ echo 'int acc_on_device(int d) { return __builtin_acc_on_device(d); } int acc_on_device_h_(int *d) { return acc_on_device(*d); }' | accel-gcc/xgcc -Baccel-gcc -x c - -o - -S -m64 -O3 -fno-builtin-acc_on_device -fno-inline
*/
#define ACC_ON_DEVICE_PTX						\
  "        .version        3.1\n"					\
  "        .target sm_30\n"						\
  "        .address_size 64\n"						\
  ".visible .func (.param.u32 %out_retval)acc_on_device(.param.u32 %in_ar1);\n" \
  ".visible .func (.param.u32 %out_retval)acc_on_device(.param.u32 %in_ar1)\n" \
  "{\n"									\
  "        .reg.u32 %ar1;\n"						\
  ".reg.u32 %retval;\n"							\
  "        .reg.u64 %hr10;\n"						\
  "        .reg.u32 %r24;\n"						\
  "        .reg.u32 %r25;\n"						\
  "        .reg.pred %r27;\n"						\
  "        .reg.u32 %r30;\n"						\
  "        ld.param.u32 %ar1, [%in_ar1];\n"				\
  "                mov.u32 %r24, %ar1;\n"				\
  "                setp.ne.u32 %r27,%r24,4;\n"				\
  "                set.u32.eq.u32 %r30,%r24,5;\n"			\
  "                neg.s32 %r25, %r30;\n"				\
  "        @%r27   bra     $L3;\n"					\
  "                mov.u32 %r25, 1;\n"					\
  "$L3:\n"								\
  "                mov.u32 %retval, %r25;\n"				\
  "        st.param.u32    [%out_retval], %retval;\n"			\
  "        ret;\n"							\
  "        }\n"								\
  ".visible .func (.param.u32 %out_retval)acc_on_device_h_(.param.u64 %in_ar1);\n" \
  ".visible .func (.param.u32 %out_retval)acc_on_device_h_(.param.u64 %in_ar1)\n" \
  "{\n"									\
  "        .reg.u64 %ar1;\n"						\
  ".reg.u32 %retval;\n"							\
  "        .reg.u64 %hr10;\n"						\
  "        .reg.u64 %r25;\n"						\
  "        .reg.u32 %r26;\n"						\
  "        .reg.u32 %r27;\n"						\
  "        ld.param.u64 %ar1, [%in_ar1];\n"				\
  "                mov.u64 %r25, %ar1;\n"				\
  "                ld.u32  %r26, [%r25];\n"				\
  "        {\n"								\
  "                .param.u32 %retval_in;\n"				\
  "        {\n"								\
  "                .param.u32 %out_arg0;\n"				\
  "                st.param.u32 [%out_arg0], %r26;\n"			\
  "                call (%retval_in), acc_on_device, (%out_arg0);\n"	\
  "        }\n"								\
  "                ld.param.u32    %r27, [%retval_in];\n"		\
  "}\n"									\
  "                mov.u32 %retval, %r27;\n"				\
  "        st.param.u32    [%out_retval], %retval;\n"			\
  "        ret;\n"							\
  "        }"

static void
link_ptx (CUmodule *module, char *ptx_code)
{
  CUjit_option opts[7];
  void *optvals[7];
  float elapsed = 0.0;
#define LOGSIZE 8192
  char elog[LOGSIZE];
  char ilog[LOGSIZE];
  unsigned long logsize = LOGSIZE;
  CUlinkState linkstate;
  CUresult r;
  void *linkout;
  size_t linkoutsize __attribute__((unused));

  gomp_plugin_notify ("attempting to load:\n---\n%s\n---\n", ptx_code);

  opts[0] = CU_JIT_WALL_TIME;
  optvals[0] = &elapsed;

  opts[1] = CU_JIT_INFO_LOG_BUFFER;
  optvals[1] = &ilog[0];

  opts[2] = CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES;
  optvals[2] = (void *) logsize;

  opts[3] = CU_JIT_ERROR_LOG_BUFFER;
  optvals[3] = &elog[0];

  opts[4] = CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES;
  optvals[4] = (void *) logsize;

  opts[5] = CU_JIT_LOG_VERBOSE;
  optvals[5] = (void *) 1;

  opts[6] = CU_JIT_TARGET;
  optvals[6] = (void *) CU_TARGET_COMPUTE_30;

  r = cuLinkCreate (7, opts, optvals, &linkstate);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuLinkCreate error: %s", cuErrorMsg (r));

  char *abort_ptx = ABORT_PTX;
  r = cuLinkAddData (linkstate, CU_JIT_INPUT_PTX, abort_ptx,
		     strlen (abort_ptx) + 1, 0, 0, 0, 0);
  if (r != CUDA_SUCCESS)
    {
      gomp_plugin_error ("Link error log %s\n", &elog[0]);
      gomp_plugin_fatal ("cuLinkAddData (abort) error: %s", cuErrorMsg (r));
    }

  char *acc_on_device_ptx = ACC_ON_DEVICE_PTX;
  r = cuLinkAddData (linkstate, CU_JIT_INPUT_PTX, acc_on_device_ptx,
		     strlen (acc_on_device_ptx) + 1, 0, 0, 0, 0);
  if (r != CUDA_SUCCESS)
    {
      gomp_plugin_error ("Link error log %s\n", &elog[0]);
      gomp_plugin_fatal ("cuLinkAddData (acc_on_device) error: %s",
			 cuErrorMsg (r));
    }

  r = cuLinkAddData (linkstate, CU_JIT_INPUT_PTX, ptx_code,
              strlen (ptx_code) + 1, 0, 0, 0, 0);
  if (r != CUDA_SUCCESS)
    {
      gomp_plugin_error ("Link error log %s\n", &elog[0]);
      gomp_plugin_fatal ("cuLinkAddData (ptx_code) error: %s", cuErrorMsg (r));
    }

  r = cuLinkComplete (linkstate, &linkout, &linkoutsize);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuLinkComplete error: %s", cuErrorMsg (r));

  gomp_plugin_notify ("Link complete: %fms\n", elapsed);
  gomp_plugin_notify ("Link log %s\n", &ilog[0]);

  r = cuModuleLoadData (module, linkout);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuModuleLoadData error: %s", cuErrorMsg (r));
}

static void
event_gc (bool memmap_lockable)
{
  struct PTX_event *ptx_event;

  gomp_plugin_mutex_lock (&PTX_event_lock);

  for (ptx_event = SLIST_FIRST (PTX_events); ptx_event;)
    {
      CUresult r;
      struct PTX_event *next = SLIST_NEXT (ptx_event, next);

      if (ptx_event->ord != PTX_dev->ord)
        goto next_event;

      r = cuEventQuery (*ptx_event->evt);
      if (r == CUDA_SUCCESS)
        {
          CUevent *te;

          te = ptx_event->evt;

	  switch (ptx_event->type)
	    {
	    case PTX_EVT_MEM:
	    case PTX_EVT_SYNC:
	      break;
	    
	    case PTX_EVT_KNL:
              {
	        /* The function gomp_plugin_async_unmap_vars needs to claim the
		   memory-map splay tree lock for the current device, so we
		   can't call it when one of our callers has already claimed
		   the lock.  In that case, just delay the GC for this event
		   until later.  */
	        if (!memmap_lockable)
		  goto next_event;

        	map_pop (ptx_event->addr);
		if (ptx_event->tgt)
		  gomp_plugin_async_unmap_vars (ptx_event->tgt);
              }
	      break;
	    }

          cuEventDestroy (*te);
          free ((void *)te);

          SLIST_REMOVE (PTX_events, ptx_event, PTX_event, next);

          free (ptx_event);
        }

    next_event:
      ptx_event = next;
    }

  gomp_plugin_mutex_unlock (&PTX_event_lock);
}

static void
event_add (enum PTX_event_type type, CUevent *e, void *h, void *tgt)
{
  struct PTX_event *ptx_event;

  assert (type == PTX_EVT_MEM || type == PTX_EVT_KNL || type == PTX_EVT_SYNC);

  ptx_event = gomp_plugin_malloc (sizeof (struct PTX_event));
  ptx_event->type = type;
  ptx_event->evt = e;
  ptx_event->addr = h;
  ptx_event->tgt = tgt;
  ptx_event->ord = PTX_dev->ord;

  gomp_plugin_mutex_lock (&PTX_event_lock);

  SLIST_INSERT_HEAD(PTX_events, ptx_event, next);

  gomp_plugin_mutex_unlock (&PTX_event_lock);
}

void
PTX_exec (void (*fn), size_t mapnum, void **hostaddrs, void **devaddrs,
	  size_t *sizes, unsigned short *kinds, int num_gangs, int num_workers,
	  int vector_length, int async, void *targ_mem_desc)
{
  struct targ_fn_descriptor *targ_fn = (struct targ_fn_descriptor *) fn;
  CUfunction function;
  CUresult r;
  int i;
  struct PTX_stream *dev_str;
  void *kargs[1];
  void *hp, *dp;
  unsigned int nthreads_in_block;

  function = targ_fn->fn;
  
  dev_str = select_stream_for_async (async, pthread_self (), false, NULL);
  assert (dev_str == current_stream);

  /* This reserves a chunk of a pre-allocated page of memory mapped on both
     the host and the device. HP is a host pointer to the new chunk, and DP is
     the corresponding device pointer.  */
  map_push (dev_str, async, mapnum * sizeof (void *), &hp, &dp);

  gomp_plugin_notify ("  %s: prepare mappings\n", __FUNCTION__);

  /* Copy the array of arguments to the mapped page.  */
  for (i = 0; i < mapnum; i++)
    ((void **) hp)[i] = devaddrs[i];

  /* Copy the (device) pointers to arguments to the device (dp and hp might in
     fact have the same value on a unified-memory system).  */
  r = cuMemcpy ((CUdeviceptr)dp, (CUdeviceptr)hp, mapnum * sizeof (void *));
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuMemcpy failed: %s", cuErrorMsg (r));

  gomp_plugin_notify ("  %s: kernel %s: launch\n", __FUNCTION__, targ_fn->name);

  // XXX: possible geometry mappings??
  //
  // OpenACC		CUDA
  //
  // num_gangs		blocks
  // num_workers	warps (where a warp is equivalent to 32 threads)
  // vector length	threads
  //

  /* The openacc vector_length clause 'determines the vector length to use for
     vector or SIMD operations'.  The question is how to map this to CUDA.

     In CUDA, the warp size is the vector length of a CUDA device.  However, the
     CUDA interface abstracts away from that, and only shows us warp size
     indirectly in maximum number of threads per block, which is a product of
     warp size and the number of hyperthreads of a multiprocessor.

     We choose to map openacc vector_length directly onto the number of threads
     in a block, in the x dimension.  This is reflected in gcc code generation
     that uses ThreadIdx.x to access vector elements.

     Attempting to use an openacc vector_length of more than the maximum number
     of threads per block will result in a cuda error.  */
  nthreads_in_block = vector_length;

  kargs[0] = &dp;
  r = cuLaunchKernel (function,
			1, 1, 1,
			nthreads_in_block, 1, 1,
			0, dev_str->stream, kargs, 0);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuLaunchKernel error: %s", cuErrorMsg (r));

#ifndef DISABLE_ASYNC
  if (async < acc_async_noval)
    {
      r = cuStreamSynchronize (dev_str->stream);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuStreamSynchronize error: %s", cuErrorMsg (r));
    }
  else
    {
      CUevent *e;

      e = (CUevent *)gomp_plugin_malloc (sizeof (CUevent));

      r = cuEventCreate (e, CU_EVENT_DISABLE_TIMING);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuEventCreate error: %s", cuErrorMsg (r));

      event_gc (true);

      r = cuEventRecord (*e, dev_str->stream);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuEventRecord error: %s", cuErrorMsg (r));

      event_add (PTX_EVT_KNL, e, (void *)dev_str, targ_mem_desc);
    }
#else
  r = cuCtxSynchronize ();
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuCtxSynchronize error: %s", cuErrorMsg (r));
#endif

  gomp_plugin_notify ("  %s: kernel %s: finished\n", __FUNCTION__,
		      targ_fn->name);

#ifndef DISABLE_ASYNC
  if (async < acc_async_noval)
#endif
    map_pop (dev_str);
}

void * openacc_get_current_cuda_context (void);

static void *
PTX_alloc (size_t s)
{
  CUdeviceptr d;
  CUresult r;

  r = cuMemAlloc (&d, s);
  if (r == CUDA_ERROR_OUT_OF_MEMORY)
    return 0;
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuMemAlloc error: %s", cuErrorMsg (r));
  return (void *)d;
}

static void
PTX_free (void *p)
{
  CUresult r;
  CUdeviceptr pb;
  size_t ps;

  r = cuMemGetAddressRange (&pb, &ps, (CUdeviceptr)p);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuMemGetAddressRange error: %s", cuErrorMsg (r));

  if ((CUdeviceptr)p != pb)
    gomp_plugin_fatal ("invalid device address");

  r = cuMemFree ((CUdeviceptr)p);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuMemFree error: %s", cuErrorMsg (r));
}

static void *
PTX_host2dev (void *d, const void *h, size_t s)
{
  CUresult r;
  CUdeviceptr pb;
  size_t ps;

  if (!s)
    return 0;

  if (!d)
    gomp_plugin_fatal ("invalid device address");

  r = cuMemGetAddressRange (&pb, &ps, (CUdeviceptr)d);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuMemGetAddressRange error: %s", cuErrorMsg (r));

  if (!pb)
    gomp_plugin_fatal ("invalid device address");

  if (!h)
    gomp_plugin_fatal ("invalid host address");

  if (d == h)
    gomp_plugin_fatal ("invalid host or device address");

  if ((void *)(d + s) > (void *)(pb + ps))
    gomp_plugin_fatal ("invalid size");

#ifndef DISABLE_ASYNC
  if (current_stream != PTX_dev->null_stream)
    {
      CUevent *e;

      e = (CUevent *)gomp_plugin_malloc (sizeof (CUevent));

      r = cuEventCreate (e, CU_EVENT_DISABLE_TIMING);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuEventCreate error: %s", cuErrorMsg (r));

      event_gc (false);

      r = cuMemcpyHtoDAsync ((CUdeviceptr)d, h, s, current_stream->stream);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuMemcpyHtoDAsync error: %s", cuErrorMsg (r));

      r = cuEventRecord (*e, current_stream->stream);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuEventRecord error: %s", cuErrorMsg (r));

      event_add (PTX_EVT_MEM, e, (void *)h, NULL);
    }
  else
#endif
    {
      r = cuMemcpyHtoD ((CUdeviceptr)d, h, s);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuMemcpyHtoD error: %s", cuErrorMsg (r));
    }

  return 0;
}

static void *
PTX_dev2host (void *h, const void *d, size_t s)
{
  CUresult r;
  CUdeviceptr pb;
  size_t ps;

  if (!s)
    return 0;

  if (!d)
    gomp_plugin_fatal ("invalid device address");

  r = cuMemGetAddressRange (&pb, &ps, (CUdeviceptr)d);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuMemGetAddressRange error: %s", cuErrorMsg (r));

  if (!pb)
    gomp_plugin_fatal ("invalid device address");

  if (!h)
    gomp_plugin_fatal ("invalid host address");

  if (d == h)
    gomp_plugin_fatal ("invalid host or device address");

  if ((void *)(d + s) > (void *)(pb + ps))
    gomp_plugin_fatal ("invalid size");

#ifndef DISABLE_ASYNC
  if (current_stream != PTX_dev->null_stream)
    {
      CUevent *e;

      e = (CUevent *)gomp_plugin_malloc (sizeof (CUevent));

      r = cuEventCreate (e, CU_EVENT_DISABLE_TIMING);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuEventCreate error: %s\n", cuErrorMsg (r));

      event_gc (false);

      r = cuMemcpyDtoHAsync (h, (CUdeviceptr)d, s, current_stream->stream);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuMemcpyDtoHAsync error: %s", cuErrorMsg (r));

      r = cuEventRecord (*e, current_stream->stream);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuEventRecord error: %s", cuErrorMsg (r));

      event_add (PTX_EVT_MEM, e, (void *)h, NULL);
    }
  else
#endif
    {
      r = cuMemcpyDtoH (h, (CUdeviceptr)d, s);
      if (r != CUDA_SUCCESS)
        gomp_plugin_fatal ("cuMemcpyDtoH error: %s", cuErrorMsg (r));
    }

  return 0;
}

static void
PTX_set_async (int async)
{
  current_stream = select_stream_for_async (async, pthread_self (), true, NULL);
}

static int
PTX_async_test (int async)
{
  CUresult r;
  struct PTX_stream *s;
  
  s = select_stream_for_async (async, pthread_self (), false, NULL);

  if (!s)
    gomp_plugin_fatal ("unknown async %d", async);

  r = cuStreamQuery (s->stream);
  if (r == CUDA_SUCCESS)
    return 1;
  else if (r == CUDA_ERROR_NOT_READY)
    return 0;

  gomp_plugin_fatal ("cuStreamQuery error: %s", cuErrorMsg (r));

  return 0;
}

static int
PTX_async_test_all (void)
{
  struct PTX_stream *s;
  pthread_t self = pthread_self ();

  gomp_plugin_mutex_lock (&PTX_dev->stream_lock);

  SLIST_FOREACH (s, &PTX_dev->active_streams, next)
    {
      if ((s->multithreaded || pthread_equal (s->host_thread, self))
	  && cuStreamQuery (s->stream) == CUDA_ERROR_NOT_READY)
	{
	  gomp_plugin_mutex_unlock (&PTX_dev->stream_lock);
	  return 0;
	}
    }

  gomp_plugin_mutex_unlock (&PTX_dev->stream_lock);

  return 1;
}

static void
PTX_wait (int async)
{
  CUresult r;
  struct PTX_stream *s;
  
  s = select_stream_for_async (async, pthread_self (), false, NULL);

  if (!s)
    gomp_plugin_fatal ("unknown async %d", async);

  r = cuStreamSynchronize (s->stream);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuStreamSynchronize error: %s", cuErrorMsg (r));
  
  event_gc (true);
}

static void
PTX_wait_async (int async1, int async2)
{
  CUresult r;
  CUevent *e;
  struct PTX_stream *s1, *s2;
  pthread_t self = pthread_self ();

  /* The stream that is waiting (rather than being waited for) doesn't
     necessarily have to exist already.  */
  s2 = select_stream_for_async (async2, self, true, NULL);

  s1 = select_stream_for_async (async1, self, false, NULL);
  if (!s1)
    gomp_plugin_fatal ("invalid async 1\n");

  if (s1 == s2)
    gomp_plugin_fatal ("identical parameters");

  e = (CUevent *)gomp_plugin_malloc (sizeof (CUevent));

  r = cuEventCreate (e, CU_EVENT_DISABLE_TIMING);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuEventCreate error: %s", cuErrorMsg (r));

  event_gc (true);

  r = cuEventRecord (*e, s1->stream);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuEventRecord error: %s", cuErrorMsg (r));

  event_add (PTX_EVT_SYNC, e, NULL, NULL);

  r = cuStreamWaitEvent (s2->stream, *e, 0);
  if (r != CUDA_SUCCESS)
    gomp_plugin_fatal ("cuStreamWaitEvent error: %s", cuErrorMsg (r));
}

static void
PTX_wait_all (void)
{
  CUresult r;
  struct PTX_stream *s;
  pthread_t self = pthread_self ();

  gomp_plugin_mutex_lock (&PTX_dev->stream_lock);

  /* Wait for active streams initiated by this thread (or by multiple threads)
     to complete.  */
  SLIST_FOREACH (s, &PTX_dev->active_streams, next)
    {
      if (s->multithreaded || pthread_equal (s->host_thread, self))
        {
	  r = cuStreamQuery (s->stream);
	  if (r == CUDA_SUCCESS)
	    continue;
	  else if (r != CUDA_ERROR_NOT_READY)
	    gomp_plugin_fatal ("cuStreamQuery error: %s", cuErrorMsg (r));

	  r = cuStreamSynchronize (s->stream);
	  if (r != CUDA_SUCCESS)
	    gomp_plugin_fatal ("cuStreamSynchronize error: %s", cuErrorMsg (r));
	}
    }

  gomp_plugin_mutex_unlock (&PTX_dev->stream_lock);

  event_gc (true);
}

static void
PTX_wait_all_async (int async)
{
  CUresult r;
  struct PTX_stream *waiting_stream, *other_stream;
  CUevent *e;
  pthread_t self = pthread_self ();
  
  /* The stream doing the waiting.  This could be the first mention of the
     stream, so create it if necessary.  */
  waiting_stream
    = select_stream_for_async (async, pthread_self (), true, NULL);
  
  /* Launches on the null stream already block on other streams in the
     context.  */
  if (!waiting_stream || waiting_stream == PTX_dev->null_stream)
    return;

  event_gc (true);

  gomp_plugin_mutex_lock (&PTX_dev->stream_lock);

  SLIST_FOREACH (other_stream, &PTX_dev->active_streams, next)
    {
      if (!other_stream->multithreaded
	  && !pthread_equal (other_stream->host_thread, self))
	continue;

      e = (CUevent *) gomp_plugin_malloc (sizeof (CUevent));

      r = cuEventCreate (e, CU_EVENT_DISABLE_TIMING);
      if (r != CUDA_SUCCESS)
	gomp_plugin_fatal ("cuEventCreate error: %s", cuErrorMsg (r));

      /* Record an event on the waited-for stream.  */
      r = cuEventRecord (*e, other_stream->stream);
      if (r != CUDA_SUCCESS)
	gomp_plugin_fatal ("cuEventRecord error: %s", cuErrorMsg (r));

      event_add (PTX_EVT_SYNC, e, NULL, NULL);

      r = cuStreamWaitEvent (waiting_stream->stream, *e, 0);
      if (r != CUDA_SUCCESS)
	gomp_plugin_fatal ("cuStreamWaitEvent error: %s", cuErrorMsg (r));
   }

  gomp_plugin_mutex_unlock (&PTX_dev->stream_lock);
}

static void *
PTX_get_current_cuda_device (void)
{
  if (!PTX_dev)
    return NULL;

  return &PTX_dev->dev;
}

static void *
PTX_get_current_cuda_context (void)
{
  if (!PTX_dev)
    return NULL;

  return PTX_dev->ctx;
}

static void *
PTX_get_cuda_stream (int async)
{
  struct PTX_stream *s;

  if (!PTX_dev)
    return NULL;

  s = select_stream_for_async (async, pthread_self (), false, NULL);

  return s ? s->stream : NULL;
}

static int
PTX_set_cuda_stream (int async, void *stream)
{
  struct PTX_stream *oldstream;
  pthread_t self = pthread_self ();

  gomp_plugin_mutex_lock (&PTX_dev->stream_lock);

  if (async < 0)
    gomp_plugin_fatal ("bad async %d", async);

  /* We have a list of active streams and an array mapping async values to
     entries of that list.  We need to take "ownership" of the passed-in stream,
     and add it to our list, removing the previous entry also (if there was one)
     in order to prevent resource leaks.  Note the potential for surprise
     here: maybe we should keep track of passed-in streams and leave it up to
     the user to tidy those up, but that doesn't work for stream handles
     returned from acc_get_cuda_stream above...  */

  oldstream = select_stream_for_async (async, self, false, NULL);
  
  if (oldstream)
    {
      SLIST_REMOVE (&PTX_dev->active_streams, oldstream, PTX_stream, next);
      
      cuStreamDestroy (oldstream->stream);
      map_fini (oldstream);
      free (oldstream);
    }

  gomp_plugin_mutex_unlock (&PTX_dev->stream_lock);

  (void) select_stream_for_async (async, self, true, (CUstream) stream);

  return 1;
}

/* Plugin entry points.  */


int
get_type (void)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s\n", __FILE__, __FUNCTION__);
#endif

  return TARGET_TYPE_NVIDIA_PTX;
}

unsigned int
get_caps (void)
{
  return TARGET_CAP_OPENACC_200;
}

const char *
get_name (void)
{
  return "nvidia";
}

int
get_num_devices (void)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s\n", __FILE__, __FUNCTION__);
#endif

  return PTX_get_num_devices ();
}

static void **kernel_target_data;
static void **kernel_host_table;

void
offload_register (void *host_table, void *target_data)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%p, %p)\n", __FILE__, __FUNCTION__,
	   host_table, target_data);
#endif
  
  kernel_target_data = target_data;
  kernel_host_table = host_table;
}

int
device_init (void)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s\n", __FILE__, __FUNCTION__);
#endif

  return PTX_init ();
}

int
device_fini (void)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s\n", __FILE__, __FUNCTION__);
#endif

  return PTX_fini ();
}

int
device_get_table (struct mapping_table **tablep)
{
  CUmodule module;
  void **fn_table;
  char **fn_names;
  int fn_entries, i;
  CUresult r;
  struct targ_fn_descriptor *targ_fns;

#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%p)\n", __FILE__, __FUNCTION__,
	   tablep);
#endif

  if (PTX_init () <= 0)
    return 0;

  /* This isn't an error, because an image may legitimately have no offloaded
     regions and so will not call GOMP_offload_register.  */
  if (kernel_target_data == NULL)
    return 0;

  link_ptx (&module, kernel_target_data[0]);

  /* kernel_target_data[0] -> ptx code
     kernel_target_data[1] -> variable mappings
     kernel_target_data[2] -> array of kernel names in ascii

     kernel_host_table[0] -> start of function addresses (_omp_func_table)
     kernel_host_table[1] -> end of function addresses (_omp_funcs_end)

     The array of kernel names and the functions addresses form a
     one-to-one correspondence.  */

  fn_table = kernel_host_table[0];
  fn_names = (char **) kernel_target_data[2];
  fn_entries = (kernel_host_table[1] - kernel_host_table[0]) / sizeof (void *);

  *tablep = gomp_plugin_malloc (sizeof (struct mapping_table) * fn_entries);
  targ_fns = gomp_plugin_malloc (sizeof (struct targ_fn_descriptor)
				 * fn_entries);

  for (i = 0; i < fn_entries; i++)
    {
      CUfunction function;

      r = cuModuleGetFunction (&function, module, fn_names[i]);
      if (r != CUDA_SUCCESS)
	gomp_plugin_fatal ("cuModuleGetFunction error: %s", cuErrorMsg (r));

      targ_fns[i].fn = function;
      targ_fns[i].name = (const char *) fn_names[i];
      
      (*tablep)[i].host_start = (uintptr_t) fn_table[i];
      (*tablep)[i].host_end = (*tablep)[i].host_start + 1;
      (*tablep)[i].tgt_start = (uintptr_t) &targ_fns[i];
      (*tablep)[i].tgt_end = (*tablep)[i].tgt_start + 1;
    }

  return fn_entries;
}

void *
device_alloc (size_t size)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%zu)\n", __FILE__, __FUNCTION__,
	   size);
#endif

  return PTX_alloc (size);
}

void
device_free (void *ptr)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%p)\n", __FILE__, __FUNCTION__, ptr);
#endif

  PTX_free (ptr);
}

void *
device_dev2host (void *dst, const void *src, size_t n)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%p, %p, %zu)\n", __FILE__,
	   __FUNCTION__, dst,
	  src, n);
#endif

  return PTX_dev2host (dst, src, n);
}

void *
device_host2dev (void *dst, const void *src, size_t n)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%p, %p, %zu)\n", __FILE__,
	   __FUNCTION__, dst, src, n);
#endif

  return PTX_host2dev (dst, src, n);
}

void (*device_run) (void *fn_ptr, void *vars) = NULL;

void
openacc_parallel (void (*fn) (void *), size_t mapnum, void **hostaddrs,
		  void **devaddrs, size_t *sizes, unsigned short *kinds,
		  int num_gangs, int num_workers, int vector_length,
		  int async, void *targ_mem_desc)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%p, %zu, %p, %p, %p, %d, %d, %d, "
	   "%d, %p)\n", __FILE__, __FUNCTION__, fn, mapnum, hostaddrs, sizes,
	   kinds, num_gangs, num_workers, vector_length, async, targ_mem_desc);
#endif

  PTX_exec (fn, mapnum, hostaddrs, devaddrs, sizes, kinds, num_gangs,
	    num_workers, vector_length, async, targ_mem_desc);
}

void *
openacc_open_device (int n)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%d)\n", __FILE__, __FUNCTION__, n);
#endif
  return PTX_open_device (n);
}

int
openacc_close_device (void *h)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%p)\n", __FILE__, __FUNCTION__, h);
#endif
  return PTX_close_device (h);
}

void
openacc_set_device_num (int n)
{
  assert (n >= 0);

  if (!PTX_dev || PTX_dev->ord != n)
    (void) PTX_open_device (n);
}

/* This can be called before the device is "opened" for the current thread, in
   which case we can't tell which device number should be returned.  We don't
   actually want to open the device here, so just return -1 and let the caller
   (oacc-init.c:acc_get_device_num) handle it.  */

int
openacc_get_device_num (void)
{
  if (PTX_dev)
    return PTX_dev->ord;
  else
    return -1;
}

bool
openacc_avail (void)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s\n", __FILE__, __FUNCTION__);
#endif
  return PTX_avail ();
}

int
openacc_async_test (int async)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%d)\n", __FILE__, __FUNCTION__,
	   async);
#endif
  return PTX_async_test (async);
}

int
openacc_async_test_all (void)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s\n", __FILE__, __FUNCTION__);
#endif
  return PTX_async_test_all ();
}

void
openacc_async_wait (int async)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%d)\n", __FILE__, __FUNCTION__,
	   async);
#endif
  PTX_wait (async);
}

void
openacc_async_wait_async (int async1, int async2)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%d, %d)\n", __FILE__, __FUNCTION__,
	   async1, async2);
#endif
  PTX_wait_async (async1, async2);
}

void
openacc_async_wait_all (void)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s\n", __FILE__, __FUNCTION__);
#endif
  PTX_wait_all ();
}

void
openacc_async_wait_all_async (int async)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%d)\n", __FILE__, __FUNCTION__,
	   async);
#endif
  PTX_wait_all_async (async);
}

void
openacc_async_set_async (int async)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%d)\n", __FILE__, __FUNCTION__,
	   async);
#endif
  PTX_set_async (async);
}

void *
openacc_get_current_cuda_device (void)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s\n", __FILE__, __FUNCTION__);
#endif
  return PTX_get_current_cuda_device ();
}

void *
openacc_get_current_cuda_context (void)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s\n", __FILE__, __FUNCTION__);
#endif
  return PTX_get_current_cuda_context ();
}

/* NOTE: This returns a CUstream, not a PTX_stream pointer.  */

void *
openacc_get_cuda_stream (int async)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%d)\n", __FILE__, __FUNCTION__,
	   async);
#endif
  return PTX_get_cuda_stream (async);
}

/* NOTE: This takes a CUstream, not a PTX_stream pointer.  */

int
openacc_set_cuda_stream (int async, void *stream)
{
#ifdef DEBUG
  fprintf (stderr, "libgomp plugin: %s:%s (%d, %p)\n", __FILE__, __FUNCTION__,
	   async, stream);
#endif
  return PTX_set_cuda_stream (async, stream);
}
