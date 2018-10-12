#include <sys/wait.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char const *argv[])
{
    int numForks;
    pid_t forkID;

    if(argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [num-forks]\n", argv[0]);

    numForks = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-forks") : 1;
    for(int i = 0; i < numForks; i++) {
        forkID = fork();
        if(forkID == 0) {
            printf("%d child\n", i);
            _exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
            printf("%d parent\n", i);
        }
    }
    return 0;
}
