#include <error_functions.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <tlpi_hdr.h>
#include <limits.h>

//测试readv 分散输入
int main(int argc, const char* argv[])
{
    //输出IOV_MAX的值
    printf("IOV_MAX: %d\n",_SC_IOV_MAX);
    //初始化buf
    struct iovec iov[3];   //定义在<sys/uio.h>
    const size_t BUFFSIZE1 = 10;
    char*        buf1      = (char*)malloc(BUFFSIZE1);
    int          buf2;
    const size_t BUFFSIZE3 = 4;
    void*        buf3      = malloc(BUFFSIZE3);
    //配置iov参数
    long sumCount   = 0;
    iov[0].iov_base = buf1;
    iov[0].iov_len  = BUFFSIZE1;
    sumCount += iov[0].iov_len;
    iov[1].iov_base = &buf2;
    iov[1].iov_len  = sizeof(int);
    sumCount += iov[1].iov_len;
    iov[2].iov_base = buf3;
    iov[2].iov_len  = BUFFSIZE3;
    sumCount += iov[2].iov_len;
    //打开文件
    int fd = open("tee_file", O_RDONLY);
    //调用readv
    long numRead;
    if ((numRead = readv(fd, iov, 3)) < 0) errExit("readv");
    if (numRead < sumCount) printf("readNum less than countNum\n");
    //输出
    printf("buf1: %s\nbuf2: %c\nbuf3: %s\n", buf1, buf2, (char*)buf3);

    free(buf1);
    free(buf3);
    return 0;
}