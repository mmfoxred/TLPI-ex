#include <asm-generic/errno-base.h>
#include <errno.h>
#include <error_functions.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "tlpi_hdr.h"

//测试使用两个错误输出函数
void _error(int argc, const char* argv[])
{
    fprintf(stderr, "EACESS: %s\n", strerror(EACCES));   //使用<string.h>
    errno = ENOENT;
    perror(argv[0]);   //使用<stdio.h>
}

//打印组ID 和用户ID
void _id_user_group(int argc, const char* argv[])
{
    printf("group_id: %d,user_id: %d \n", getgid(), getuid());
}

//测试read读终端输入遇到\n会结束
void _read_in_term()
{
    const size_t MAXN = 20;
    char         buffer[MAXN];
    ssize_t      num = read(STDIN_FILENO, buffer, MAXN - 1);
    if(num==-1)
        fprintf(STDERR_FILENO, "errno read");
    buffer[num] = '\0';
    printf("input: %s\n",buffer);
}

//测试tlpi_hdr库
void _tlpi_lib()
{
    errMsg("test this lib \n%s","hello world\n");
    // usageErr("test usageErr\n");
}

//测试getopt()
void _getopt(int argc,const char* argv[])
{
    int o;
    const char* optstring = "abc:";
    while((o = getopt(argc, argv, optstring)) != -1)
    {
        switch (o) {
        case 'a':
            printf("opt is a,optarg is %s\n",optarg);
            break;
        case'b':
            printf("opt is b,optarg is %s\n",optarg);
            break;
        case 'c':
            printf("opt is c,optarg is %s\n",optarg);
            break;
        case '?':
            printf("opterr:%d\n",opterr);
            printf("optopt: %c\n",optopt);
            break;
        default:
            printf("default\n");
        }
    }
}

int main(int argc, const char* argv[])
{
    _getopt(argc, argv);
    return 0;
}