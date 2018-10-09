#include <sys/xattr.h>
#include "../lib/tlpi_hdr.h"

#define XATTR_SIZE 10000

static void usageError(char *progName) {
    fprintf(stderr, "Usage: %s [-x] file...\n", progName);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    char list[XATTR_SIZE], value[XATTR_SIZE];
    ssize_t listLen, valueLen;
    int ns, j, k, opt;
    Boolean hexDisplay;

    for(j = 1; j < argc; j++) {
        listLen = listxattr(argv[j], list, XATTR_SIZE);
        if(listLen == -1)
            errExit("listxattr");
        printf("%s: %s\n", argv[j], list);
        for(ns = 0; ns < listLen; ns += strlen(&list[ns]) + 1) {
            printf("        name=%s; ", &list[ns]);
            valueLen = getxattr(argv[j], &list[ns], value, XATTR_SIZE);
            if(valueLen == -1) {
                printf("couldn't get value");
            } else if(!hexDisplay) {
                printf("value=%.*s", (int)valueLen, value);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
