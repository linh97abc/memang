gcc -g -O3 -Isubsys\include subsys\init_array.c subsys\memmang\mem_slab.c test\test-mem_slab.c -o main.exe -Wl,-Map=main.map
@REM gcc -g -O0 -Isubsys\include subsys\memmang\heap-validate.c subsys\memmang\heap.c test\test-sys-heap.c -o main.exe
