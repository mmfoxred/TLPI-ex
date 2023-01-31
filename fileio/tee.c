#include <error_functions.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <tlpi_hdr.h>
#include <unistd.h>

int main(int argc, const char* argv[])
{
    //参数个数检查
    if (argc < 2 || (strcmp("--help", argv[1])) == 0) usageErr("%s ..\n", argv[0]);
    //打开文件
    int*   fd    = (int*)malloc(sizeof(int) * (argc));
    int    flags = O_RDWR | O_CREAT | O_TRUNC;
    mode_t mode  = S_IRGRP | S_IROTH | S_IRUSR | S_IWGRP | S_IWOTH | S_IWUSR;
    //处理-a参数
    int count = argc;
    if (strcmp(argv[argc - 1], "-a") == 0)
    {
        --count;
        flags = O_RDWR | O_APPEND;
    }

    //批量打开
    for (int i = 1; i < count; i++)
    {
        fd[i] = open(argv[i], flags, mode);
        if (fd[i] == -1)
        {
            errMsg("error in open[%d]", i);
            for (int j = 1; j < i; j++)   //回收fd
                close(fd[j]);
            exit(-1);
        }
    }
    //读取标准输入 并写入到各个文件
    int   numRead,numWrite;
    void* buf[BUFSIZ];
    while ((numRead = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
    {
        for (int i = 1; i < count; i++)
        {
            if ((numWrite = write(fd[i], buf, numRead)) < numRead) errMsg("error in write[%d]", i);
        }
    }
    if (numRead < 0) errExit("error in read");
    //释放资源
    for(int i=1;i<count;i++)
    {
        if(close(fd[i])<0)
            errMsg("error in close fd[%d]",i);
    }

    return 0;
}