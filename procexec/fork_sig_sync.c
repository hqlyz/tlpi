#define _DEFAULT_SOURCE
#include <signal.h>
#include "../time/curr_time.h"
#include "../lib/tlpi_hdr.h"

#define SIG_SYNC SIGUSR1

static void handler(int sig) {
    // do nothing
}

int main(int argc, char const *argv[])
{
    pid_t childPID;
    sigset_t blockMask, origMask, emptyMask;
    struct sigaction sa;

    setbuf(stdout, NULL);
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIG_SYNC);
    if(sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
        errExit("sigprocmask");
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    if(sigaction(SIG_SYNC, &sa, NULL) == -1)
        errExit("sigaction");
    switch(childPID = fork()) {
        case -1:
            errExit("fork");
        case 0:
            printf("[%s %ld] Child started - doing some work\n",
                currTime("%T"), (long)getpid());
            sleep(2);
            printf("[%s %ld] Child about to signal parnet\n",
                currTime("%T"), (long)getpid());
            if(kill(getppid(), SIG_SYNC) == -1)
                errExit("kill");
            _exit(EXIT_SUCCESS);
        default:
            printf("[%s %ld] Parent about to wait for signal\n",
                currTime("%T"), (long)getpid());
            sigemptyset(&emptyMask);
            if(sigsuspend(&emptyMask) == -1 && errno != EINTR)
                errExit("sigsuspend");
            printf("[%s %ld] Parent got signal\n",
                currTime("%T"), (long)getpid());
            if(sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
                errExit("sigprocmask");
            exit(EXIT_SUCCESS);
    }
}
