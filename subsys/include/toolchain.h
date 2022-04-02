#ifndef _TOOLCHAIN_H_
#define _TOOLCHAIN_H_

/**
 * @def HAS_BUILTIN(x)
 * @brief Check if the compiler supports the built-in function \a x.
 *
 * This macro is for use with conditional compilation to enable code using a
 * builtin function that may not be available in every compiler.
 */
#ifdef __has_builtin
#define HAS_BUILTIN(x) __has_builtin(x)
#else
/*
 * The compiler doesn't provide the __has_builtin() macro, so instead we depend
 * on the toolchain-specific headers to define HAS_BUILTIN_x for the builtins
 * supported.
 */
#define HAS_BUILTIN(x) HAS_BUILTIN_##x
#endif


#ifdef __GNUC__
#define ARG_UNUSED(x) (void)(x)
#define AT_SECTION(sec) __attribute__((section(#sec)))
#define __used __attribute__((used))

#if defined(__WIN32) || defined(__WIN64) ||  defined(__linux) || defined(__unix) || defined(__posix)
#define SECTION_PRE_INIT AT_SECTION(preinit_array)
#define SECTION_INIT AT_SECTION(init_array)

extern void* __start_preinit_array;
extern void* __start_init_array;
extern void* __stop_preinit_array;
extern void* __stop_init_array;
#define __preinit_array_start __start_preinit_array
#define __preinit_array_end __stop_preinit_array
#define __init_array_start __start_init_array
#define __init_array_end __stop_init_array
#else
#define SECTION_PRE_INIT AT_SECTION(.preinit_array)
#define SECTION_INIT AT_SECTION(.init_array)
#endif
#elif defined(__MSVC__)
#error "don't support"
#pragma section(".pinit$a")
#pragma section(".pinit$u")
#pragma section(".pinit$z")
#pragma section(".init$a")
#pragma section(".init$u")
#pragma section(".init$z")

#define ARG_UNUSED(x) (void)(x)
#define AT_SECTION(sec) __declspec(allocate(#sec))
#define SECTION_PRE_INIT AT_SECTION(.pinit$u)
#define SECTION_INIT AT_SECTION(.init$u)
#define __used

/*
AT_SECTION(.pinit$a) void *pre_init_section_start = (void*)0;
AT_SECTION(.pinit$z) void *pre_init_section_end = (void*)0;
AT_SECTION(.init$a) void *init_section_start = (void*)0;
AT_SECTION(.init$z) void *init_section_end = (void*)0;
*/

#else
#define ARG_UNUSED(x) (void)(x)
#define AT_SECTION(sec)
#define __used
#define SECTION_PRE_INIT
#define SECTION_INIT
#endif

/**
 * @brief Run an initialization function at boot
 * @param _init_fn Pointer to the boot function to run
 */
#define SYS_INIT(_init_fn)  __used SECTION_INIT void (*_sys_init_##_init_fn)(void) = _init_fn;

/**
 * @brief Run an initialization function at boot (before SYS_INIT)
 * @param _init_fn Pointer to the boot function to run
 */
#define SYS_PRE_INIT(_init_fn)  __used SECTION_PRE_INIT void (*_sys_preinit_##_init_fn)(void) = _init_fn;

#ifdef __cplusplus
extern "C" {
#endif
extern void do__int_array(void);
#ifdef __cplusplus
}
#endif
#endif /* _TOOLCHAIN_H_ */
