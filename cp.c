#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char* argv[])
{
    //参数个数判断
    if (argc != 3 || (strcmp(argv[1], "h--help") == 0))
    {
        fprintf(stderr, "Usage:...\n");
        return 0;
    }
    //源文件打开
    int flags_src = O_RDONLY;   //用到了<fcntl.h>
    int fd_src    = open(argv[1], flags_src);
    if (fd_src == -1) perror(argv[0]);
    //目标文件
    int    flag_target = O_WRONLY | O_CREAT | O_TRUNC;
    mode_t mode_target = S_IWUSR | S_IWGRP | S_IWOTH | S_IRUSR | S_IROTH | S_IRGRP;
    int    fd_target   = open(argv[2], flag_target, mode_target);
    if (fd_target == -1) perror(argv[0]);
    //复制
    ssize_t      numCount;
    const size_t BUFFSIZE = 1024;
    void*        buf[1024];
    while ((numCount = read(fd_src, buf, BUFFSIZE)) > 0)
    {
        if (write(fd_target, buf, numCount) != numCount)
            fprintf(stderr, "could't write whole buffer\n");
    }
    if (numCount < 0) fprintf(stderr, "read error!\n");
    //关闭
    if (close(fd_src) == -1) fprintf(stderr, "close error!\n");
    if (close(fd_target) == -1) fprintf(stderr, "close error!\n");

    return 0;
}