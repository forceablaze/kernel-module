#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "kernel_api.h"

inline void *operator new(size_t s)
{
	return my_alloc(s);
}

inline void operator delete(void *p)
{
	return my_free(p);
}

#endif
