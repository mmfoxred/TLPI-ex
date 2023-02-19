#include <error_functions.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlpi_hdr.h>

//修改进程环境
extern char** environ;
int           main(int argc, const char* argv[])
{
    clearenv();
    //添加
    for (int i = 1; i < argc; i++)
    {
        if (putenv(argv[i]) != 0)
            errExit("putenv");
    }
    //添加GREET变量
    if (setenv("GREET", "Hello World", 0) == -1)
        errExit("setenv");
    //移除BYE变量
    if (unsetenv("BYE") == -1)
        errExit("unsetenv");
    //输出当前的环境变量列表
    char** env;
    for (env = environ; *env != NULL; env++)
        puts(*env);
    return 0;
}