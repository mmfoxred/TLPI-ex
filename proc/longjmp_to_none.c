#include <setjmp.h>
#include <stdio.h>
#include <tlpi_hdr.h>

//练习6-2 longjmp 跳到一个已经返回的函数会怎样
static jmp_buf env;
static void    return_func()
{
    printf("now in return_func\n");
    setjmp(env);
    return;
}

int main(int argc, const char* argv[])
{
    printf("now in main_start\n");
    printf("exec return_func\n");
    return_func();
    printf("jmp\n");
    longjmp(env, 1);
    printf("now in main_end\n");
    return 0;
}