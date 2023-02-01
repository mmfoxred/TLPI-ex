#include <error_functions.h>
#include <fcntl.h>
#include <get_num.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlpi_hdr.h>
#include <unistd.h>

//练习5-2
void ex5_2()
{
    //打开文件
    int flags = O_WRONLY | O_APPEND;
    int fd    = open("tee_file", flags);
    if (fd == -1) errExit("open");
    //置文件偏移于文件起始处
    if (lseek(fd, 0, SEEK_SET) == -1) errExit("lseek");
    //写入数据
    char buf[] = "\nwrite after lseek to SEEK_SET\n";
    if (write(fd, buf, strlen(buf)) == -1) errExit("write");

    close(fd);
}

//练习5-3
void ex5_3(int argc, const char* argv[])
{
    //参数检查
    if (argc < 3 || argc > 4 || strcmp(argv[1], "--help") == 0) usageErr("%s\n", argv[0]);
    //打开文件
    int    flags = O_WRONLY | O_CREAT | O_APPEND;
    mode_t mode  = S_IWUSR | S_IWGRP | S_IWOTH;
    bool hasx = (argc == 4 && !strcmp(argv[3],"x"));
    if (hasx)   //有参数x
    {
        flags = O_WRONLY | O_CREAT;
    }
    int fd = open(argv[1], flags, mode);
    if (fd == -1) errExit("open");
    //写入字节
    int num_bytes = getLong(argv[2], GN_ANY_BASE, "argv[2]");
    for (int i = 0; i < num_bytes; i++)
    {
        if(hasx)
        {
            lseek(fd, 0, SEEK_END);
        }
        if (write(fd, "*", 1) < 0) 
            errExit("write");
    }
}

int main(int argc, const char* argv[])
{
    ex5_3(argc, argv);
    return 0;
}