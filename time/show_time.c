#include <error_functions.h>
#include <locale.h>
#include <stdio.h>
#include <time.h>
#include <tlpi_hdr.h>
#define BUFFSIZE 1024

//时区对ctime localtime mktime strftime的影响
// LC_TIME LC_ALL LANG的优先级
int main(int argc, const char* argv[])
{
    if (setlocale(LC_ALL, "") == NULL)
        errExit("setlocale");
    time_t      t       = time(NULL);
    const char* strtime = ctime(&t);
    printf("ctime of time() value is :%s", strtime);
    struct tm* tm_local = localtime(&t);
    printf("localtime of time() value is :%s", asctime(tm_local));
    char s[BUFFSIZE];
    if (strftime(s, BUFFSIZE, "%A,%d %B %Y %T", tm_local) == 0)
        errExit("strftime");
    printf("strftime of localtime() value is :%s\n", s);
    return 0;
}