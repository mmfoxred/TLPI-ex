#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, const char* argv[])
{
    //判断参数个数是否合法 + help
    if (argc < 3 || (strcmp(argv[1], "--help") == 0))
    {
        fprintf(stderr, "Usage:\n%s filepath {r<length|R<length|w<string>|s<offset>}\n", argv[0]);
        return 0;
    }

    //打开文件
    int    flags = O_RDWR | O_CREAT;
    mode_t mode  = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;   // rw-rw-rw
    int    fd    = open(argv[1], flags, mode);
    if (fd == -1)
    {
        perror(argv[0]);
        printf("\n");
    }
    printf("open file succeded\n");

    //处理参数
    for (int i = 2; i < argc; i++)
    {
        char  choice = argv[i][0];
        int   len;
        int   numCount;
        char* buf;
        switch (choice)
        {
        //读操作
        case 'r':
        case 'R':
            len      = atoi(&argv[i][1]);
            buf      = malloc(len);
            numCount = read(fd, buf, len);
            if (numCount == -1) fprintf(stderr, "error in read\n");
            printf("%s:\n", argv[i]);
            for (int j = 0; j < numCount; j++)
            {
                if (choice == 'r')   //以文本形式输出
                    printf("%c", buf[j] ? buf[j] : '?');
                else   //以十六进制输出
                    printf("%02x ", buf[j]);
            }
            printf("\n");
            free(buf);
            break;
        //写操作
        case 'w':
            len      = strlen(&argv[i][1]);
            buf      = &argv[i][1];
            numCount = write(fd, buf, len);
            if (numCount == -1) fprintf(stderr, "error in write\n");
            printf("%s: write %dbytes\n", argv[i], len);
            break;
        // seek操作
        case 's':
            len = atoi(&argv[i][1]);
            if (lseek(fd, len, SEEK_SET) == -1) fprintf(stderr, "error in lseek\n");
            printf("%s: seek succeeded\n", argv[i]);
            break;
        default:
            fprintf(stderr, "Argument error\n");
        }
    }
    return 0;
}