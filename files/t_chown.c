#include "../users_groups/ugid.h"
#include <error_functions.h>
#include <pwd.h>
#include <tlpi_hdr.h>
#include <unistd.h>

//改变文件的属主和属组
int main(int argc, const char* argv[])
{
    //参数判断
    if (argc < 3 || strcmp(argv[1], "-help") == 0)
        usageErr("\n");
    uid_t uid = -1;
    if (strcmp(argv[1], "-") != 0)
        uid = uid_from_name(argv[1]);
    gid_t gid = -1;
    if (strcmp(argv[2], "-") != 0)
        gid = gid_from_gname(argv[2]);
    for (int i = 3; i < argc; i++)
    {
        if (chown(argv[i], uid, gid) == -1)
            errExit("chown");
    }
    return 0;
}