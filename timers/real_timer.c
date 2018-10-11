#define _DEFAULT_SOURCE
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include "../lib/tlpi_hdr.h"

static sig_atomic_t gotAlarm = 0;

void displayTimer(const char *msg, Boolean includeTimer) {
    static int callNum = 0;
    static struct timeval startTime;
    struct timeval curTime;
    struct itimerval itv;

    if(callNum == 0) {
        printf("        Elapsed Value   Interval\n");
        gettimeofday(&startTime, NULL);
    }
    if(gettimeofday(&curTime, NULL) == -1)
        errExit("gettimeofday");
    printf("%7s %6.2f", msg, (curTime.tv_sec - startTime.tv_sec) + 
        (curTime.tv_usec - startTime.tv_usec) / 1000000.0);
    
    if(includeTimer) {
        if(getitimer(ITIMER_REAL, &itv) == -1)  
            errExit("getitimer");
        printf("%6.2f %6.2f", (itv.it_value.tv_sec + itv.it_value.tv_usec / 1000000.0),
            (itv.it_interval.tv_sec + itv.it_interval.tv_usec / 1000000.0));
    }
    printf("\n");
    callNum++;
}

void alarmHandler(int sig) {
    gotAlarm = 1;
}

int main(int argc, char const *argv[])
{
    struct sigaction sa;
    struct itimerval itv;
    time_t itValueSec, itValueUsec, itIntervalSec, itIntervalUsec;
    int maxSig = 3;
    if(argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s it-value-sec it-value-usec it-interval-sec it-interval-usec", argv[0]);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = alarmHandler;
    if(sigaction(SIGALRM, &sa, NULL) == -1)
        errExit("sigaction");
    itValueSec = (argc > 1) ? getInt(argv[1], 0, "it-value-sec") : 5;
    itValueUsec = (argc > 2) ? getInt(argv[2], 0, "it-value-usec") : 0;
    itIntervalSec = (argc > 3) ? getInt(argv[3], 0, "it-interval-sec") : 0;
    itIntervalUsec = (argc > 4) ? getInt(argv[4], 0, "it-interval-usec") : 0;
    
    itv.it_value.tv_sec = itValueSec;
    itv.it_value.tv_usec = itValueUsec;
    itv.it_interval.tv_sec = itIntervalSec;
    itv.it_interval.tv_usec = itIntervalUsec;

    displayTimer("START:", FALSE);

    if(setitimer(ITIMER_REAL, &itv, NULL) == -1)
        errExit("setitimer");
    while(maxSig > 0) {
        if(!gotAlarm)
            displayTimer("Main:", TRUE);
        else {
            displayTimer("ALARM:", TRUE);
            maxSig--;
            gotAlarm = 0;
            if(itv.it_interval.tv_sec == 0 && itv.it_interval.tv_usec == 0)
                break;
        }
        sleep(1);
    }
    return 0;
}
