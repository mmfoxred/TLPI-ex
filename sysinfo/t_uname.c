#include <error_functions.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <tlpi_hdr.h>

//使用uname
int main(int argc, const char* argv[])
{
    struct utsname uts;
    if (uname(&uts) == -1)
        errExit("uanme");
    printf("Node name: %s\n", uts.nodename);
    printf("sysname %s\n", uts.sysname);
    printf("machine: %s\n", uts.machine);
    printf("release: %s\n", uts.release);
    printf("version: %s\n", uts.version);
    return 0;
}