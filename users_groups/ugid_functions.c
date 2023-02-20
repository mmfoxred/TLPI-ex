#include <crypt.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <tlpi_hdr.h>

// user name from user_id
char* uname_from_id(uid_t user_id)
{
    struct passwd* pw = getpwuid(user_id);
    return pw == NULL ? NULL : pw->pw_name;
}
// uid from user name
uid_t uid_from_name(const char* uname)
{
    if (uname == NULL || *uname == "\0")
        return -1;
    //值类型的uname
    char* endptr;
    uid_t u = strtol(uname, &endptr, 10);
    if (*endptr == '\0')
        return u;
    struct passwd* pw = getpwnam(uname);
    return pw == NULL ? -1 : pw->pw_uid;
}

gid_t gid_from_gname(const char* gname)
{
    if (gname == NULL || *gname == '\0')
        return -1;
    char* endptr;
    gid_t g = strtol(gname, &endptr, 10);
    if (*endptr == '\0')
        return g;
    struct group* grp = getgrnam(gname);
    return grp == NULL ? -1 : grp->gr_gid;
}

char* gname_from_gid(gid_t gid)
{
    struct group* grp = getgrgid(gid);
    return grp == NULL ? NULL : grp->gr_name;
}

int main(int argc, const char* argv[])
{
    uid_t       uid   = 1000;
    const char* uname = "1000";
    // printf("uname:%s uid:%d\n", uname_from_id(uid), uid);
    // printf("uname:%d uid:%s\n", uid_from_name(uname), uname);
    gid_t       gid   = 4;
    const char* gname = "adm";
    printf("gid:%d gname:%s\n", gid_from_gname(gname), gname);
    printf("gname:%s gid:%d\n", gname_from_gid(gid), gid);
    return 0;
}