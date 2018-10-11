#include <stdio.h>
#include <stdlib.h>

void printSigset(FILE *, const char *, const sigset_t *);

int printSigMask(FILE *, const char *);

int printPendingSigs(FILE *, const char *);