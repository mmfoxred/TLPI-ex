#include <errno.h>
#include <error_functions.h>
#include <stdio.h>
#include <tlpi_hdr.h>
#include <unistd.h>

//使用fpathconf 函数
void use_fpathconf(const char* msg, int fd, int name)
{
    long lim = fpathconf(fd, name);
    if (lim != -1)   //读取成功
        printf("%s: %ld\n", msg, lim);
    else
    {
        if (errno == 0)   //未定义
            printf("%s: 未定义\n", msg);
        else
            errExit("fpathconf");
    }
}

int main(int argc, const char* argv[])
{
    use_fpathconf("_PC_NAME_MAX", STDIN_FILENO, _PC_NAME_MAX);
    use_fpathconf("_PC_PATH_MAX", STDIN_FILENO, _PC_PATH_MAX);
    use_fpathconf("_PC_PIPE_BUF", STDIN_FILENO, _PC_PIPE_BUF);
    return 0;
}