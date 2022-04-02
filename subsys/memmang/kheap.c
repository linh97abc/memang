/*
 * Copyright (c) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sys/sys_heap.h>
#include <toolchain.h>
#include <kheap.h>



void k_heap_init(struct k_heap *h, void *mem, size_t bytes)
{
	// z_waitq_init(&h->wait_q);
	sys_heap_init(&h->heap, mem, bytes);

}


void *k_heap_aligned_alloc(struct k_heap *h, size_t align, size_t bytes)
{
	void *ret;

	// k_spinlock_key_t key = k_spin_lock(&h->lock);
	ret = sys_heap_aligned_alloc(&h->heap, align, bytes);
	// k_spin_unlock(&h->lock, key);

	return ret;
}

void *k_heap_alloc(struct k_heap *h, size_t bytes)
{
	return k_heap_aligned_alloc(h, sizeof(void *), bytes);
}

void k_heap_free(struct k_heap *h, void *mem)
{
	// k_spinlock_key_t key = k_spin_lock(&h->lock);
	sys_heap_free(&h->heap, mem);
	//	k_spin_unlock(&h->lock, key);
}
