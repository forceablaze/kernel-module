#include "operator.h"
#include "cpp_interface.h"
#include "hello.h"

static Hello *hello = 0;

void __start()
{
	hello = new Hello();
}

void __stop()
{
	if(hello)
		delete hello;
}
