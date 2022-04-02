gcc -g -O3 -Isubsys\include subsys\init_array.c subsys\memmang\mem_slab.c subsys\delegate.c subsys\linklist.c test\test-delegate.c -o main.exe -Wl,-Map=main.map
