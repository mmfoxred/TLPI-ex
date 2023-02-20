#include <asm-generic/errno-base.h>
#include <crypt.h>
#include <errno.h>
#include <error_functions.h>
#include <pwd.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlpi_hdr.h>
#include <unistd.h>

int main(int argc, const char* argv[])
{
    //读取user name
    long userName_limit = sysconf(_SC_LOGIN_NAME_MAX);
    if (userName_limit == -1)
        userName_limit = 256;
    char* uname = (char*)malloc(userName_limit);
    printf("Username: ");
    fflush(stdout);
    if (fgets(uname, userName_limit, stdin) == NULL)
        errExit("fgets");
    long len = strlen(uname);
    if (uname[len - 1] == '\n')
        uname[len - 1] = '\0';
    //读取passwd shadow 文件
    struct passwd* pwd = getpwnam(uname);
    if (pwd == NULL)
        fatal("could not get password record.");
    struct spwd* sp = getspnam(uname);
    if (sp == NULL && errno == EACCES)
        fatal("no permission to read shadow password file");
    if (sp != NULL)
        pwd->pw_passwd = sp->sp_pwdp;
    //读取密码
    char* password = getpass("Password: ");
    //加密
    char* encrypted = crypt(password, pwd->pw_passwd);
    if (encrypted == NULL)
        errExit("encrypted");
    //清除未加密密码
    char* p = password;
    while (*p != '\0')
        *p++ = '\0';
    //认证
    if (strcmp(encrypted, pwd->pw_passwd) == 0)
        printf("Successfully authenticated.UID: %ld passwd: %s\n", (long)pwd->pw_uid, pwd->pw_passwd);
    else
        errExit("Incorrect password");
    return 0;
}