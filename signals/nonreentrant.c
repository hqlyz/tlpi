#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "../lib/tlpi_hdr.h"

#define KEY "jskksjsjsjj"
#define SALT "te"

void *crypt2Handler(int sig) {
    crypt(KEY, SALT);
}

struct sigaction *crypt2(int sig) {
    struct sigaction sa;
    sigset_t ss;
    sigemptyset(&ss);
    sigaddset(&ss, SIG_BLOCK);
    sa.sa_mask = ss;
    sa.__sigaction_handler = crypt2Handler;
    return &sa;
}

int main(int argc, char const *argv[])
{
    if(argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("Usage: %s str1 str2", argv[0]);

    printf("Before cryption: %s\n", crypt(KEY, SALT));
    sigaction(SIGINT, crypt2, NULL);
    return 0;
}
