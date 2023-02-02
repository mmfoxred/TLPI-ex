#include <bits/types/struct_iovec.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <tlpi_hdr.h>
#include <unistd.h>

//使用 read()、write()以及 malloc 函数包（见 7.1.2 节）中的必要函数以实现 readv()和 writev()功能

ssize_t readv_my(int fd, const struct iovec* iov, int iovcnt)
{
    // IOV_MAX检查
    if (iovcnt > _SC_IOV_MAX || iovcnt < 0) exit(-1);
    ssize_t numRead, numReadSum = 0;
    for (int i = 0; i < iovcnt; i++)
    {
        void*  buf     = iov[i].iov_base;
        size_t iov_len = iov[i].iov_len;
        if ((numRead = read(fd, buf, iov_len)) < 0) return -1;
        if (numRead < iov_len) return 0;
        numReadSum += numRead;
    }
    return numReadSum;
}

ssize_t writev_my(int fd, const struct iovec* iov, int iovcnt)
{
    // IOV_MAX检查
    if (iovcnt > _SC_IOV_MAX || iovcnt < 0) exit(-1);
    ssize_t numWrite, numWriteSum = 0;
    for (int i = 0; i < iovcnt; i++)
    {
        void*  buf     = iov[i].iov_base;
        size_t iov_len = iov[i].iov_len;
        if ((numWrite = write(fd, buf, iov_len)) < 0) return -1;   // error
        if (numWrite < iov_len) return 0;                          // EOF
        numWriteSum += numWrite;
    }
    return numWriteSum;   // buf is full
}

int main(int argc, const char* argv[])
{
    //初始化buf
    struct iovec iov[3];   //定义在<sys/uio.h>
    const size_t BUFFSIZE1 = 10;
    char*        buf1      = (char*)malloc(BUFFSIZE1);
    char         buf2;
    const size_t BUFFSIZE3 = 40;
    void*        buf3      = malloc(BUFFSIZE3);
    //配置iov参数
    long sumCount   = 0;
    iov[0].iov_base = buf1;
    iov[0].iov_len  = BUFFSIZE1;
    sumCount += iov[0].iov_len;
    iov[1].iov_base = &buf2;
    iov[1].iov_len  = sizeof(char);
    sumCount += iov[1].iov_len;
    iov[2].iov_base = buf3;
    iov[2].iov_len  = BUFFSIZE3;
    sumCount += iov[2].iov_len;
    //打开文件
    int fd = open("tee_file", O_RDONLY);
    //调用readv
    long numRead;
    if ((numRead = readv_my(fd, iov, 3)) < 0) errExit("readv");
    if (numRead < sumCount) printf("readNum less than countNum\n");
    //输出
    printf("buf1: %s\nbuf2: %c\nbuf3: %s\n", buf1, buf2, (char*)buf3);
    free(buf1);
    free(buf3);
    return 0;
}