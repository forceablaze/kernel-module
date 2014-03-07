#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

void* my_alloc(size_t s)
{
	return kmalloc(s, GFP_KERNEL);
}

void my_free(void *p)
{
	kfree(p);
}

void test(void)
{
	printk("%s\n", __func__);
}
