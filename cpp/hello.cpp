#include "hello.h"
#include "kernel_api.h"

Hello::Hello()
{
	printk("hello\n");
}

void Hello::hello()
{
	printk("%s\n", __func__);
}
