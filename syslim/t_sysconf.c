#include <errno.h>
#include <error_functions.h>
#include <stdio.h>
#include <tlpi_hdr.h>
#include <unistd.h>

//使用sysconf() 函数
void use_sysconf(const char* msg, int name)
{
    long lim = sysconf(name);
    if (lim != -1)   //获取到了
        printf("%s: %ld\n", msg, lim);
    else
    {
        if (errno == 0)   // 没出错，未定义
            printf("%s: 未定义\n", msg);
        else   //出错了
            errExit("sysconf");
    }
}

int main(int argc, const char* argv[])
{
    use_sysconf("SC_ARG_MAX", _SC_ARG_MAX);
    use_sysconf("_SC_LOGIN_NAME_MAX", _SC_LOGIN_NAME_MAX);
    use_sysconf("SC_OPEN_MAX", _SC_OPEN_MAX);
    return 0;
}