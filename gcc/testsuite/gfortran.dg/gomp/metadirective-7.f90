! { dg-do compile }
! { dg-additional-options "-fdump-tree-gimple" }

program main
  integer, parameter :: N = 256
contains
  subroutine f (a, num)
    integer :: a(N)
    integer :: num
    integer :: i

    !$omp metadirective &
    !$omp& when (target_device={device_num(num), kind("gpu"), arch("nvptx")}: &
    !$omp&       target parallel do map(tofrom: a(1:N))) &
    !$omp& when (target_device={device_num(num), kind("gpu"), &
    !$omp&                      arch("amdgcn"), isa("gfx906")}: &
    !$omp&       target parallel do) &
    !$omp& when (target_device={device_num(num), kind("cpu"), arch("x86_64")}: &
    !$omp&       parallel do)
      do i = 1, N
	a(i) = a(i) + i
      end do

    !$omp metadirective &
    !$omp& when (target_device={kind("gpu"), arch("nvptx")}: &
    !$omp&       target parallel do map(tofrom: a(1:N)))
      do i = 1, N
	a(i) = a(i) + i
      end do
  end subroutine
end program

! { dg-final { scan-tree-dump "__builtin_GOMP_evaluate_target_device \\(.+, &\"gpu.x00\"\\\[0\\\], &\"amdgcn.x00\"\\\[0\\\], &\"gfx906.x00\"\\\[0\\\]\\)" "gimple" } }
! { dg-final { scan-tree-dump "__builtin_GOMP_evaluate_target_device \\(.+, &\"gpu.x00\"\\\[0\\\], &\"nvptx.x00\"\\\[0\\\], 0B\\)" "gimple" } }
! { dg-final { scan-tree-dump "__builtin_GOMP_evaluate_target_device \\(.+, &\"cpu.x00\"\\\[0\\\], &\"x86_64.x00\"\\\[0\\\], 0B\\)" "gimple" } }
! { dg-final { scan-tree-dump "__builtin_GOMP_evaluate_target_device \\(-2, &\"gpu.x00\"\\\[0\\\], &\"nvptx.x00\"\\\[0\\\], 0B\\)" "gimple" } }
