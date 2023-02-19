#include <setjmp.h>
#include <stdio.h>
#include <tlpi_hdr.h>

//使用setjmp 和 longjmp

static jmp_buf env;
static void    f2()
{
    longjmp(env, 2);
}
static void f1(int argc)
{
    if (argc == 1)
        longjmp(env, 1);
    f2();
}

int main(int argc, const char* argv[])
{
    switch (setjmp(env))
    {
    case 0:
        printf("setjmp init,call f1(),return 0\n");
        f1(argc);
        break;
    case 1:
        printf("setjmp return,return 1\n");
        break;
    case 2:
        printf("setjmp return,return 2\n");
        break;
    }
    return 0;
}