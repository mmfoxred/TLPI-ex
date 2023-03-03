#define _BSD_SOURCE
#include <error_functions.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <tlpi_hdr.h>

//获取并解释文件的stat信息
static void displayStatInfo(const struct stat* sb)
{
    if (sb == NULL)
        errExit("displayStatInfo");
    char* type = NULL;
    switch (sb->st_mode & S_IFMT)
    {
    case S_IFREG:
        type = "Regular File";
        break;
    case S_IFDIR:
        type = "directory";
        break;
    case S_IFIFO:
        type = "FIFO or pipe";
        break;
    case S_IFLNK:
        type = "symbolic (soft) link";
        break;
    case S_IFSOCK:
        type = "socket";
        break;
    case S_IFCHR:
        type = "character device";
        break;
    case S_IFBLK:
        type = "block device";
        break;
    default:
        type = "unknown file type";
    }
    //文件类型
    printf("File Type: %s\n", type);
    //设备主、辅ID
    // printf("Device Containing i-node: Major: %ld,minor: %ld\n", (long)major(sb->st_dev), (long)minor(sb->st_dev));
    printf("Device Containing i-node: Major: %ld\n", sb->st_dev);
    printf("I-node number: %ld\n", sb->st_ino);
    printf("Mode :%lo\n", (unsigned long)sb->st_mode);
    if (sb->st_mode & (S_ISUID | S_ISGID | S_ISVTX))
        printf("special bit set:%s%s%s\n",
               sb->st_mode & S_ISUID ? "Set-UID" : "",
               sb->st_mode & S_ISGID ? "Set-GID" : "",
               sb->st_mode & S_ISVTX ? "Set-sticky" : "");
    printf("Number of (hard) link:%ld\n", sb->st_nlink);
    printf("Ownership: UID=%d GID=%d\n", sb->st_uid, sb->st_gid);
    printf("File Size = %ld bytes\n", sb->st_size);
    printf("Optimal IO block size: %ld bytes\n", sb->st_blksize);
    printf("512B blocks allocated: %lld\n", (long long)sb->st_blocks);
    printf("Last file access: %s\n", ctime(&sb->st_atim.tv_sec));
    printf("Last file modify: %s\n", ctime(&sb->st_mtim.tv_sec));
    printf("Last status change: %s\n", ctime(&sb->st_ctim.tv_sec));
}

int main(int argc, const char* argv[])
{
    //参数判断
    if (argc < 2)
        usageErr("\n");
    bool l_stat = false;
    if (argc == 3 && strcmp(argv[2], "-l"))
        l_stat = true;
    const char* filepath = argv[1];
    struct stat buf;
    if (l_stat)   //加了参数-l
    {
        if (lstat(filepath, &buf) == -1)
            errExit("lstat");
    }
    else
    {
        if (stat(filepath, &buf) == -1)
            errExit("stat");
    }
    displayStatInfo(&buf);
    return 0;
}