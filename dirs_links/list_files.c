#include <dirent.h>
#include <errno.h>
#include "../lib/tlpi_hdr.h"

static void listFiles(const char *filePath) {
    DIR *pathp;
    struct dirent *dp;
    Boolean isCurrentDir;

    isCurrentDir = strcmp(filePath, ".") == 0;
    if((pathp = opendir(filePath)) == NULL)
        errExit("opendir");
    
    while((dp = readdir(pathp)) != NULL) {
        errno = 0;
        if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        if(!isCurrentDir)
            printf("%s/", filePath);
        printf("%s\n", dp->d_name);
    }

    if(errno != 0)
        errExit("readdir");

    if(closedir(pathp) == -1)
        errExit("closedir");
}

int main(int argc, char const *argv[])
{
    if(argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("Usage: %s [dir...]", argv[1]);

    if(argc == 1)
        listFiles(".");
    else {
        for(argv++; *argv; argv++)
            listFiles(*argv);
    }
    return 0;
}
