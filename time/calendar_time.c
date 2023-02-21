#include <bits/types/struct_timeval.h>
#include <error_functions.h>
#include <locale.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <tlpi_hdr.h>
#define SECONDS_IN_TROPICAL_YEAR (365.24219 * 24 * 60 * 60)

//对比格林威治时间（GMT）与本地时区时间
int main(int argc, const char* argv[])
{
    //时间戳
    const time_t time_now = time(NULL);
    printf(
        "Seconds since the Epoch(1 Jan 1970):%ld (about %6.3f years)\n", time_now, time_now / SECONDS_IN_TROPICAL_YEAR);
    struct timeval tmv;   //这里要用值类型，而不能是指针类型？
    if (gettimeofday(&tmv, NULL) == -1)
        exit(-1);
    // errExit("gettimeofday");
    printf("gettimeofday() returned %ld seconds,%ld microsecs\n", tmv.tv_sec, tmv.tv_usec);
    //分解时间
    printf("Broken down by gmtime():\n");
    struct tm* tm_gm = gmtime(&time_now);   // gmtime
    printf("year=%d mon=%d mday=%d hour=%d min=%d sec=%d wday=%d yday=%d idst=%d\n",
           tm_gm->tm_year,
           tm_gm->tm_mon,
           tm_gm->tm_mday,
           tm_gm->tm_hour,
           tm_gm->tm_min,
           tm_gm->tm_sec,
           tm_gm->tm_wday,
           tm_gm->tm_yday,
           tm_gm->tm_isdst);
    printf("Broken down by localtime():\n");
    struct tm* tm_local = localtime(&time_now);   // localtime
    //实际上tm_gm == tm_local,ctime gmtime localtime asctime返回的字符串或tm结构体都是静态数据，它们共享的。
    //那么这里就会改变tm_gm，变成和tm_local一样的值.
    printf("year=%d mon=%d mday=%d hour=%d min=%d sec=%d wday=%d yday=%d idst=%d\n",
           tm_local->tm_year,
           tm_local->tm_mon,
           tm_local->tm_mday,
           tm_local->tm_hour,
           tm_local->tm_min,
           tm_local->tm_sec,
           tm_local->tm_wday,
           tm_local->tm_yday,
           tm_local->tm_isdst);
    //还原tm_gm
    tm_gm = gmtime(&time_now);
    //转字符串
    const char* strtime_gm = asctime(tm_gm);
    printf("asctime() formats the gmtime() value as: %s", strtime_gm);   // asctime和ctime会在字符串末尾自动添加\n
    const char* strtime_ctime = ctime(&time_now);   //这个改变字符串，还会改变tm结构体
    printf("ctime() formats the time() value as: %s", strtime_ctime);
    // broken down time to time_t
    //还原tm_gm
    tm_gm             = gmtime(&time_now);
    time_t gm_to_time = mktime(tm_gm);
    printf("mktime() of gmtime() value: %ld secs\n", gm_to_time);
    //还原tm_local
    tm_local             = localtime(&time_now);
    time_t local_to_time = mktime(tm_local);
    printf("mktime() of localtime() value: %ld secs\n", local_to_time);
    return 0;
}