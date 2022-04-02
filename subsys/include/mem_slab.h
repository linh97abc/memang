#ifndef __MEM_SLAB_H_
#define __MEM_SLAB_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief MEMORY SLAB CONTROL
     * @param free_list    Pointer to list of free memory blocks
     * @param blkSize      Size (in bytes) of each block of memory 
     * @param numBlks      Total number of blocks in this partition  
     * @param numFreeBlks  Number of memory blocks remaining in this partition
     */
    struct mem_slab
    {
        void *free_list;
        uint32_t blkSize;
        uint32_t numBlks;
        uint32_t numFreeBlks;
    };

    /**
     * @brief Create a fixed-sized memory partition that will be managed by mem_slab object.
     * @param pmem    is a pointer to the memory partition control block
     * @param buffer  is the starting address of the memory partition
     * @param size    is the number of memory blocks to create from the partition.
     * @param blksize is the size (in bytes) of each block in the memory partition.
     * @retval A pointer to the partition was created
     * @retval A pointer to NULL if the partition was not created because of invalid arguments.
     */
    struct mem_slab *mem_slab_create(struct mem_slab *pmem, void *buffer, uint32_t size, uint32_t blksize);

    /**
     * @brief Get a memory block from a partition
     * @param pmem    is a pointer to the memory partition control block
     * @retval A pointer to a memory block if no error is detected
     * @retval A pointer to NULL if an error is detected
     */
    void *mem_slab_alloc(struct mem_slab *pmem);

    /**
     * @brief Returns a memory block to a partition
     * @param pmem    is a pointer to the memory partition control block
     * @param pblk    is a pointer to the memory block being released.
     * @param size    is the number of memory blocks to create from the partition.
     * @param blksize is the size (in bytes) of each block in the memory partition.
     * @retval 0      if the memory block was inserted into the partition
     * @retval -1     if you are returning a memory block to an already FULL memory
     *                partition (You freed more blocks than you allocated!)
     */
    int8_t mem_slab_free(struct mem_slab *pmem, void *pblk);

#ifdef __cplusplus
}
#endif

#endif
