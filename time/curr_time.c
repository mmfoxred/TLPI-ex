#include <error_functions.h>
#include <stdio.h>
#include <time.h>
#include <tlpi_hdr.h>
#define BUFF_SIZE 1024

//返回当前时间的字符串 使用strftime()
int main(int argc, const char* argv[])
{
    time_t     time_now   = time(NULL);
    struct tm* time_local = localtime(&time_now);
    if (time_local == NULL)
        errExit("localtime");
    static char stime[BUFF_SIZE];
    strftime(stime, BUFF_SIZE, "%Y-%m-%d %T\n", time_local);
    printf("%s", stime);
    return 0;
}