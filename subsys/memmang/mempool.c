/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sys/sys_heap.h>
#include <sys/__assert.h>
#include <sys/util.h>
#include <toolchain.h>
#include <kheap.h>


#if HAS_BUILTIN(__builtin_mul_overflow)

static inline bool size_mul_overflow(size_t a, size_t b, size_t *result)
{
	return __builtin_mul_overflow(a, b, result);
}
#else /* !use_builtin(__builtin_mul_overflow) */

static inline bool size_mul_overflow(size_t a, size_t b, size_t *result)
{
	size_t c = a * b;

	*result = c;

	return a != 0 && (c / a) != b;
}
#endif /* use_builtin(__builtin_mul_overflow) */

void k_free(void *ptr)
{
	struct k_heap **heap_ref;

	if (ptr != NULL) {
		heap_ref = ptr;
		ptr = --heap_ref;

		k_heap_free(*heap_ref, ptr);

	}
}

static struct k_heap _system_heap;
#define _SYSTEM_HEAP (&_system_heap)

#define CONFIG_HEAP_MEM_POOL_SIZE 512
static uintptr_t s_stack[CONFIG_HEAP_MEM_POOL_SIZE/sizeof(uintptr_t)]; 

static void _system_heap_init(void)
{
	sys_heap_init(&_system_heap, s_stack, ROUND_DOWN(CONFIG_HEAP_MEM_POOL_SIZE, sizeof(uintptr_t)));
}

SYS_PRE_INIT(_system_heap_init)

void *k_aligned_alloc(size_t align, size_t size)
{
	__ASSERT(align / sizeof(void *) >= 1
		&& (align % sizeof(void *)) == 0,
		"align must be a multiple of sizeof(void *)");

	__ASSERT((align & (align - 1)) == 0,
		"align must be a power of 2");

	void *ret = k_heap_aligned_alloc(_SYSTEM_HEAP, align, size);

	return ret;
}

void *k_malloc(size_t size)
{
	void *ret = k_aligned_alloc(sizeof(void *), size);

	return ret;
}

void *k_calloc(size_t nmemb, size_t size)
{
	void *ret;
	size_t bounds;


	if (size_mul_overflow(nmemb, size, &bounds)) {

		return NULL;
	}

	ret = k_malloc(bounds);
	if (ret != NULL) {
		(void)memset(ret, 0, bounds);
	}


	return ret;
}

