#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_READ 20 

int main(int argc, char const *argv[])
{
    char buf[MAX_READ + 1];
    ssize_t numRead;

    while((numRead = read(STDIN_FILENO, buf, MAX_READ)) == -1) {
        perror("read");
        exit(1);
    }
    buf[numRead] = '\0';
    printf("result: %s\n", buf);
    return 0;
}
