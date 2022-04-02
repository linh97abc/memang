#include <sys/sys_heap.h>

struct k_heap {
	struct sys_heap heap;
};

/** @brief Allocate aligned memory from a k_heap
 *
 * Behaves in all ways like k_heap_alloc(), except that the returned
 * memory (if available) will have a starting address in memory which
 * is a multiple of the specified power-of-two alignment value in
 * bytes.  The resulting memory can be returned to the heap using
 * k_heap_free().
 *
 * @note @a timeout must be set to K_NO_WAIT if called from ISR.
 * @note When CONFIG_MULTITHREADING=n any @a timeout is treated as K_NO_WAIT.
 *
 * @funcprops \isr_ok
 *
 * @param h Heap from which to allocate
 * @param align Alignment in bytes, must be a power of two
 * @param bytes Number of bytes requested
 * @param timeout How long to wait, or K_NO_WAIT
 * @return Pointer to memory the caller can now use
 */
void *k_heap_aligned_alloc(struct k_heap *h, size_t align, size_t bytes);

/**
 * @brief Allocate memory from a k_heap
 *
 * Allocates and returns a memory buffer from the memory region owned
 * by the heap.  If no memory is available immediately, the call will
 * block for the specified timeout (constructed via the standard
 * timeout API, or K_NO_WAIT or K_FOREVER) waiting for memory to be
 * freed.  If the allocation cannot be performed by the expiration of
 * the timeout, NULL will be returned.
 *
 * @note @a timeout must be set to K_NO_WAIT if called from ISR.
 * @note When CONFIG_MULTITHREADING=n any @a timeout is treated as K_NO_WAIT.
 *
 * @funcprops \isr_ok
 *
 * @param h Heap from which to allocate
 * @param bytes Desired size of block to allocate
 * @param timeout How long to wait, or K_NO_WAIT
 * @return A pointer to valid heap memory, or NULL
 */
void *k_heap_alloc(struct k_heap *h, size_t bytes);

/**
 * @brief Free memory allocated by k_heap_alloc()
 *
 * Returns the specified memory block, which must have been returned
 * from k_heap_alloc(), to the heap for use by other callers.  Passing
 * a NULL block is legal, and has no effect.
 *
 * @param h Heap to which to return the memory
 * @param mem A valid memory block, or NULL
 */
void k_heap_free(struct k_heap *h, void *mem);
