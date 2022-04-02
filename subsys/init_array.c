#include <stdint.h>
#include <toolchain.h>

#if defined(__WIN32) || defined(__WIN64) ||  defined(__linux) || defined(__unix) || defined(__posix)
static void nop(void) 
{
}

SYS_INIT(nop)
SYS_PRE_INIT(nop)
#endif

void do__int_array(void)
{
	uintptr_t func_pointer_start = (uintptr_t)&__preinit_array_start;
	uintptr_t func_pointer_end = (uintptr_t)&__preinit_array_end;

	while (func_pointer_start < func_pointer_end)
	{
		void (**p)(void);
		/* get function pointer */
		p = (void (**)(void))func_pointer_start;
		(*p)();
		func_pointer_start += sizeof(p);
	}

	func_pointer_start = (uintptr_t)&__init_array_start;
	func_pointer_end = (uintptr_t)&__init_array_end;

	while (func_pointer_start < func_pointer_end)
	{
		void (**p)(void);
		/* get function pointer */
		p = (void (**)(void))func_pointer_start;
		(*p)();
		func_pointer_start += sizeof(p);
	}
}