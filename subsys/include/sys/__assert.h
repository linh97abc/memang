/*
 * Copyright (c) 2011-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _INCLUDE_SYS___ASSERT_H_
#define _INCLUDE_SYS___ASSERT_H_

#include <stdbool.h>
#include <stdio.h>

#ifdef CONFIG_ASSERT
#ifndef __ASSERT_ON
#define __ASSERT_ON 1
#endif
#endif

#ifdef CONFIG_FORCE_NO_ASSERT
#undef __ASSERT_ON
#define __ASSERT_ON 0
#endif

#if defined(CONFIG_ASSERT_VERBOSE)
#include <stdio.h>
#define __ASSERT_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else /* CONFIG_ASSERT_VERBOSE */
#define __ASSERT_PRINT(fmt, ...)
#endif /* CONFIG_ASSERT_VERBOSE */


#define __ASSERT_LOC(test)                          \
	__ASSERT_PRINT("ASSERTION FAIL [%s] @ %s:%d\n", #test, __FILE__, __LINE__)
#define __ASSERT_MSG_INFO(fmt, ...) __ASSERT_PRINT("\t" fmt "\n", ##__VA_ARGS__)

#ifdef __ASSERT_ON

#ifdef __cplusplus
extern "C"
{
#endif

void assert_post_action();
#define __ASSERT_POST_ACTION() assert_post_action()

#ifdef __cplusplus
}
#endif

#define __ASSERT_NO_MSG(test)       \
	do                              \
	{                               \
		if (!(test))                \
		{                           \
			__ASSERT_LOC(test);     \
			__ASSERT_POST_ACTION(); \
		}                           \
	} while (false)

#define __ASSERT(test, fmt, ...)                   \
	do                                             \
	{                                              \
		if (!(test))                               \
		{                                          \
			__ASSERT_LOC(test);                    \
			__ASSERT_MSG_INFO(fmt, ##__VA_ARGS__); \
			__ASSERT_POST_ACTION();                \
		}                                          \
	} while (false)

#else
#define __ASSERT(test, fmt, ...) {}
#define __ASSERT_NO_MSG(test) {}
#endif

#endif /* _INCLUDE_SYS___ASSERT_H_ */
