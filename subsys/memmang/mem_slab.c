#include <mem_slab.h>
#include <os_abstract.h>
#include <sys/util.h>

#define ALIGNED_MASK (sizeof(void *) - 1)

struct mem_slab *mem_slab_create(struct mem_slab *pmem, void *buffer, uint32_t size, uint32_t blksize)
{
    void **pblk;
    void **plink;
    int32_t i;
    uint32_t nblks;

    void **addr_aligned;
    uint32_t blksize_aligned;
    uint32_t __blksize; /* = block size / sizeof(void*) */

    if ((size < blksize) || !pmem || !buffer)
    {
        return ((struct mem_slab *)0);
    }

    addr_aligned = (void **)ROUND_UP(buffer, sizeof(void *));
    blksize_aligned = (uint32_t)ROUND_UP(blksize, sizeof(void *));
    __blksize = blksize_aligned / sizeof(void *);

    nblks = (size - ((sizeof(void *) - ((uintptr_t)buffer & ALIGNED_MASK)) & ALIGNED_MASK)) / blksize_aligned;

    plink = (void **)addr_aligned; /* Create linked list of free memory blocks      */
    pblk = addr_aligned + __blksize;

    for (i = 0; i < (nblks - 1); i++)
    {
        *plink = (void *)pblk; /* Save pointer to NEXT block in CURRENT block   */
        plink = pblk;          /* Position to  NEXT      block                  */
        pblk += __blksize;     /* Point to the FOLLOWING block                  */
    }

    *plink = (void *)0;                 /* Last memory block points to NULL              */
    pmem->free_list = addr_aligned; /* Initialize pointer to pool of free blocks     */
    pmem->numFreeBlks = nblks;          /* Store number of free blocks in MCB            */
    pmem->numBlks = nblks;
    pmem->blkSize = blksize_aligned; /* Store block size of each memory blocks        */

    return (pmem);
}

void *mem_slab_alloc(struct mem_slab *pmem)
{
    void *pblk;

    OS_CPU_SR_DEFINE;
    
    OS_ENTER_CRITICAL();
    pblk = pmem->numFreeBlks? pmem->free_list:NULL; 
    if (pblk)
    {                                         /* See if there are any free memory blocks       */
        pmem->free_list = *(void **)pblk; /*      Adjust pointer to new free list          */
        pmem->numFreeBlks--;                  /*      One less memory block in this partition  */
    }
    OS_EXIT_CRITICAL();

    return (pblk); /*      Return memory block to caller            */
}

int8_t mem_slab_free(struct mem_slab *pmem, void *pblk)
{
    OS_CPU_SR_DEFINE;

    OS_ENTER_CRITICAL();
    if (pmem->numFreeBlks >= pmem->numBlks)
    { /* Make sure all blocks not already returned          */
        OS_EXIT_CRITICAL();
        return -1;
    }
    *(void **)pblk = pmem->free_list; /* Insert released block into free block list         */
    pmem->free_list = pblk;
    pmem->numFreeBlks++; /* One more memory block in this partition            */
    OS_EXIT_CRITICAL();

    return 0; /* Notify caller that memory block was released       */
}
