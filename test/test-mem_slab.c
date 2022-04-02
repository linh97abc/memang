#include <stdio.h>
#include <mem_slab.h>
#include <toolchain.h>

uint64_t stack[2];
struct mem_slab mem;
void mem_init(void)
{
  mem_slab_create(&mem, &stack, sizeof(stack), 8);
}

void preinit(void)
{
  puts(__func__);
}

SYS_INIT(mem_init)
SYS_PRE_INIT(preinit)

int main ()
{
    do__int_array();

    void * a1, *a2;

    a1 = mem_slab_alloc(&mem);
    printf("addr: %x\n", a1);

    a2 = mem_slab_alloc(&mem);
    printf("addr: %x\n", a2);

    mem_slab_free(&mem, a1);
    a1 = mem_slab_alloc(&mem);
    printf("addr: %x\n", a1);

    a2 = mem_slab_alloc(&mem);
    printf("addr: %x\n", a2);

    a1 = mem_slab_alloc(&mem);
    printf("addr: %x\n", a1);

    return 0;
}