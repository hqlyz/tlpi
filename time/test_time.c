#include <stdio.h>
#include "curr_time.h"

int main(int argc, char const *argv[])
{
    char *format = "%c";
    printf("%s\n", currTime(NULL));
    return 0;
}
