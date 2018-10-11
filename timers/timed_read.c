#define _DEFAULT_SOURCE
#include <signal.h>
#include "../lib/tlpi_hdr.h"

#define BUF_SIZE 200

static void signalrmHandler(int sig) {
    printf("Caught signal\n");
}

int main(int argc, char const *argv[])
{
    if(argc > 1 && strcmp(argv[0], "--help") == 0)
        usageErr("%s [num-secs [restart-flag]]\n", argv[0]);
    return 0;
}
