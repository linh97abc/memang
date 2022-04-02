#include <stdio.h>
#include <delegate.h>
#include <toolchain.h>

void func1(void* p)
{
    puts(__func__);
}

void func2(void* p)
{
    puts(__func__);
}
void func3(void* p)
{
    puts(__func__);
}
void func4(void* p)
{
    puts(__func__);
}

int main()
{
    struct delegate d = {.begin = NULL};

    do__int_array();

    delegate_add(&d, func1);
    delegate_add(&d, func2);
    delegate_invoke(&d);

    delegate_add(&d, func3);
    delegate_add(&d, func4);

    delegate_invoke(&d);

    delegate_remove(&d, func3);
    delegate_invoke(&d);

    delegate_delete(&d);

    delegate_invoke(&d);

    return 0;
}