#include <error_functions.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <tlpi_hdr.h>
#include <unistd.h>

//验证文件描述符及其副本是否共享了文件偏移量和打开文件的状态标志。
int main(int argc, const char* argv[])
{
    //打开文件
    int flags = O_RDWR;
    int fd    = open("tfile", flags);
    if (fd == -1) errExit("open fd");
    int fd_copy = dup(fd);
    //测试 文件偏移量
    off_t off_old1 = lseek(fd, 0, SEEK_CUR);
    off_t off_old2 = lseek(fd_copy, 0, SEEK_CUR);
    lseek(fd, 5, SEEK_CUR);
    off_t off_new1 = lseek(fd, 0, SEEK_CUR);
    off_t off_new2 = lseek(fd_copy, 0, SEEK_CUR);
    if (off_old1 == off_old2 && off_new1 == off_new2) printf("文件偏移量共享\t");
    //测试 打开文件的状态标志
    int flags_old1 = fcntl(fd, F_GETFL);
    int flags_old2 = fcntl(fd_copy, F_GETFL);
    fcntl(fd_copy, F_SETFL, flags_old1|O_APPEND);
    int flags_new1 = fcntl(fd, F_GETFL);
    int flags_new2 = fcntl(fd_copy, F_GETFL);
    if(flags_new1 == flags_new2)
        printf("打开文件的状态标志共享\n");
    close(fd);
    close(fd_copy);
    return 0;
}