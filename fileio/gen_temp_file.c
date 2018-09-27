#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char template[] = "/tmp/jlXXXXXX";
    int fd;

    fd = mkstemp(template);
    if(fd == -1) {
        perror("create temp file");
        exit(1);
    }
    unlink(template);
    write(fd, "test", 4);
    close(fd);
    return 0;
}
