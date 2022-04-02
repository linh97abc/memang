#ifndef __SYSMEM_INTERNAL_H__
#define __SYSMEM_INTERNAL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __ucosii__
#if OS_CRITICAL_METHOD == 3
#define OS_CPU_SR_DEFINE OS_CPU_SR cpu_sr = 0;
#else
#define OS_CPU_SR_DEFINE ((void)0)
#endif

#else
#define OS_CPU_SR_DEFINE ((void)0)
#define OS_ENTER_CRITICAL() ((void)0)
#define OS_EXIT_CRITICAL() ((void)0)

#endif

#ifdef __cplusplus
}
#endif

#endif
