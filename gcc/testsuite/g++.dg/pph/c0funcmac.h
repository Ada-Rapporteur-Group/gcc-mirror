#ifndef C0FUNCMAC_H
#define C0FUNCMAC_H
#define gnu_dev_major(dev) long dev
#define gnu_dev_minor(dev) short dev
#define major(dev) gnu_dev_major (dev)
#define minor(dev) gnu_dev_minor (dev)
#endif
