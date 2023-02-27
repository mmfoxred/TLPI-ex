#include <error_functions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define _XOPEN_SOURCE
#include <fcntl.h>
#include <tlpi_hdr.h>

//读写/proc内文件
int main(int argc, const char* argv[])
{
    //打开文件
    int flags = argc > 1 ? O_RDWR : O_RDONLY;
    int fd    = open("/proc/sys/kernel/pid_max", flags);
    if (fd == -1)
        errExit("open");
    //读取内容
    unsigned int buffSize = 1024;
    char*        buf      = malloc(buffSize);
    int          n        = read(fd, buf, buffSize);
    if (n == -1)
        errExit("read");
    printf("Old value: %s\n", buf);
    //写内容
    if (argc > 1)
    {
        n = write(fd, argv[1], strlen(argv[1]));
        if (n != strlen(argv[1]))
            errExit("write");
    }
    system("echo now: ;cat /proc/sys/kernel/pid_max");
    free(buf);
    return 0;
}