#ifndef __KERNEL_API_H__
#define __KERNEL_API_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int size_t;
#define KERN_INFO "<6>"
#define NULL 0UL

extern void printk(const char *fmt, ...);
extern void* my_alloc(size_t s);
extern void my_free(void *p);

#ifdef __cplusplus
}
#endif

#endif
