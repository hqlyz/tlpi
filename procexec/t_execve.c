#include "../lib/tlpi_hdr.h"

int main(int argc, char const *argv[])
{
    char *argVec[10];
    char *envVec[] = {"GREET=salut", "BYE=adiue", NULL};

    if(argc != 2 || strcmp(argVec[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);

    argVec[0] = strrchr(argv[1], '/');
    printf("argVec[0]: %s\n", argVec[0]);
    if(argVec[0] != NULL)
        argVec[0]++;
    else
        argVec[0] = argv[1];
    argVec[1] = "hello world";
    argVec[2] = "goodbye";
    argVec[3] = NULL;

    execve(argv[1], argVec, envVec);
    errExit("execve");
}
