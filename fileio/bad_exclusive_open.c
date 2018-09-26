#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include "../lib/tlpi.h"

int main(int argc, char const *argv[])
{
    int fd;
    fd = open(argv[1], O_WRONLY);
    if(fd != -1) {
        printf("[PID %ld] File \"%s\" already exists\n", (long)getpid(), argv[1]);
        close(fd);
    } else {
        if(errno != ENOENT) {
            errExit("open");
        } else {
            fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
            if(fd == -1)
                errExit("open");
            printf("[PID %ld] Created file \"%s\" exclusively\n", (long)getpid(), argv[1]);
            close(fd);
        }
    }
    return 0;
}
