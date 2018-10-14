#define _XOPEN_SOURCE 600
// #define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "../lib/tlpi_hdr.h"

#define SALT "te"

char *str2;

void crypt2Handler(int sig) {
    crypt(str2, SALT);
}

int main(int argc, char const *argv[])
{
    char *r1;
    if(argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("Usage: %s str1 str2", argv[0]);

    str2 = strdup(argv[2]);
    printf("%s\n", str2);

    // r1 = crypt(argv[1], SALT);
    r1 = strdup(crypt(argv[1], SALT));

    struct sigaction sa;
    // sigset_t ss;
    // sigemptyset(&ss);
    // sigaddset(&ss, SIGINT);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = crypt2Handler;
    sigaction(SIGINT, &sa, NULL);

    while(1) {
        // printf("After cryption: %s\n", crypt(argv[1], SALT));
        // sleep(1);
        if(strcmp(crypt(argv[1], SALT), r1) != 0)
            printf("mismatch\n");
    }

    return 0;
}
