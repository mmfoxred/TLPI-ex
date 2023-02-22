#include <get_num.h>
#include <unistd.h>
#define _XOPEN_SOURCE
#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include <tlpi_hdr.h>

// times 和 clock

void process_time(const char* msg)
{
    if (msg != NULL)
        printf("%s", msg);
    // clock
    clock_t clock_now = clock();
    printf("clock() returns: %ld clocks-per-sec (%.2f secs\n", clock_now, (double)clock_now / CLOCKS_PER_SEC);
    // times
    struct tms tms_now;
    long       clockTicks = sysconf(_SC_CLK_TCK);
    times(&tms_now);
    printf("times() yields: user CPU=%.2f; system CPU=%2.f\n",
           (double)tms_now.tms_utime / clockTicks,
           (double)tms_now.tms_stime / clockTicks);
}

int main(int argc, const char* argv[])
{
    printf("CLOCK_PER_SEC=%ld sysconf(_SC_CLK_TCK)=%ld\n", CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));
    process_time("At program start:\n");
    for (int i = 0; i < getInt(argv[1], GN_GT_0, "loopCount"); i++)
        getppid();
    process_time("After getppid() loop:\n");
    return 0;
}