#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

static void doJump(int nvar, int rvar, int vvar) {
    printf("Inside doJump(): nvar=%d rvar=%d vvar=%d\n", nvar, rvar, vvar);
    longjmp(env, 1);
}

int main(int argc, char const *argv[])
{
    int nvar = 111;
    register int rvar = 222;
    volatile int vvar = 333;

    if(setjmp(env) == 0) {
        nvar = 777;
        rvar = 888;
        vvar = 999;
        doJump(nvar, rvar, vvar);
    } else {
        printf("After doJump(): nvar=%d rvar=%d vvar=%d\n", nvar, rvar, vvar);
    }
    return 0;
}
