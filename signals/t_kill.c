#define _DEFAULT_SOURCE
#include <signal.h>
#include <sys/types.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char const *argv[])
{
    int sigNum, result;

    if(argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("Usage: %s pid sig-num\n", argv[0]);

    sigNum = getInt(argv[2], 0, "sigNum");
    result = kill(getLong(argv[1], 0, "pid"), sigNum);

    if(sigNum != 0) {
        if(result == -1)
            errExit("kill");
    } else {
        if(result == 0)
            printf("Process exists and we can send it a signal\n");
        else if(errno == EPERM) 
            printf("Process exists, but we don't have permission to ");
        else if(errno == ESRCH)
            printf("Process does not exist\n");
        else
            errExit("kill");
    }

    return 0;
}
