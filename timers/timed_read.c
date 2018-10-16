#define _DEFAULT_SOURCE
#include <signal.h>
#include "../lib/tlpi_hdr.h"

#define BUF_SIZE 200

static void signalrmHandler(int sig) {
    printf("Caught signal\n");
}

int main(int argc, char const *argv[])
{
    struct sigaction sa;
    char buf[BUF_SIZE];
    ssize_t numRead;
    int savedErrno;

    if(argc > 1 && strcmp(argv[0], "--help") == 0)
        usageErr("%s [num-secs [restart-flag]]\n", argv[0]);
    sa.sa_flags = (argc > 2) ? SA_RESTART : 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = signalrmHandler;
    if(sigaction(SIGALRM, &sa, NULL) == -1)
        errExit("sigaction");

    alarm((argc > 1) ? getInt(argv[1], GN_NONNEG, "num-secs") : 10);
    numRead = read(STDIN_FILENO, buf, BUF_SIZE - 1);
    savedErrno = errno;
    alarm(0);
    errno = savedErrno;

    if(numRead == -1) {
        if(errno == EINTR)
            printf("Read timed out\n");
        else
            errMsg("read");
    } else {
        printf("Successful read (%ld bytes): %.*s\n", (long)numRead, (int)numRead - 2, buf);
    }
    return 0;
}
