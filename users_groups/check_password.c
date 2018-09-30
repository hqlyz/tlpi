#define _BSD_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char const *argv[])
{
    char *username, *password, *encrypted, *p;
    struct passwd *pwd;
    struct spwd *spwd;
    Boolean authOk;
    size_t len;
    long lnmax;
    lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    if(lnmax == -1)
        lnmax = 256;
    username = malloc(lnmax);
    if(username == NULL)
        errExit("malloc");
    printf("Username: ");
    fflush(stdout);
    if(fgets(username, lnmax, stdin) == NULL)
        exit(EXIT_FAILURE);
    len = strlen(username);
    if(username[len - 1] = '\n')
        username[len - 1] = '\0';
    pwd = getpwnam(username);
    if(pwd == NULL)
        fatal("couldn't get password record");
    
    return 0;
}
