#define _XOPEN_SOURCE
#include <error_functions.h>
#include <locale.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <tlpi_hdr.h>
#define BUFF_SIZE 1024

//输入一个时间字符串 将它转换成一个时间 再输出
int main(int argc, const char* argv[])
{
    //参数判断
    if (argc < 3)
        usageErr("\n");
    const char* strtime = argv[1];
    //转换成time_t
    struct tm* tp;
    strptime(strtime, argv[2], tp);
    time_t tm_t = mktime(tp);
    printf("time seconds:%ld\n", tm_t);
    //再输出为字符串
    static char strtime_p[BUFF_SIZE];
    const char* formatStr = argc == 4 ? argv[3] : "%c";
    strftime(strtime_p, BUFF_SIZE, formatStr, tp);
    printf("%s\n", strtime_p);
    return 0;
}