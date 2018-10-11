#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void signalHandler(int sig) {
    static int count = 0;
    if(sig == SIGINT) {
        printf("\nOuch (%d)\n", count++);
        return;
    }
    printf("\nCaught SIGQUIT, let's quit\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    if(signal(SIGINT, signalHandler) == SIG_ERR)
        errExit("sigint");
    if(signal(SIGQUIT, signalHandler) == SIG_ERR)
        errExit("sigquit");
    while(1) 
        pause();
    return 0;
}
