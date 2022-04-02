#include <sys/sys_heap.h>
#include <stdio.h>
#include <stdint.h>

struct sys_heap heap;
uint8_t stack[64];

int main()
{
    char *s;

    sys_heap_init(&heap, stack, sizeof(stack));

    s = sys_heap_alloc(&heap, 3);
    s[0] = 'a';
    s[1] = 'b';
    s[2]= 'c';

    printf("%x", s);

    s = sys_heap_alloc(&heap, 3);
    s[0] = 'a';
    s[1] = 'b';
    s[2]= 'c';

    printf("%x", s);

    s = sys_heap_alloc(&heap, 3);
    s[0] = 'a';
    s[1] = 'b';
    s[2]= 'c';

    printf("%x", s);

    sys_heap_free(&heap, s);
    printf("%x", s);

    s = sys_heap_alloc(&heap, 3);
    s[0] = 'a';
    s[1] = 'b';
    s[2]= 'c';

    printf("%x", s);

    return 0;
}