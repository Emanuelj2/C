#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>

void
Spin(int n)
{
    double t = 0;                   //traker
    struct timeval start, now;      //declars two time snapshots

    gettimeofday(&start, NULL);
    while(t < n)
    {
        gettimeofday(&now, NULL);
        t = (now.tv_sec - start.tv_sec) +               // second
            (now.tv_usec - start.tv_usec) / 1000000.0;  // microseconds
    }
}


int 
main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "usage: cpu <string>\n");
        exit(1);
    }
    char *str = argv[1];
    while(1)
    {
        Spin(1);
        printf("%s\n", str);
    }
    return 0;
}
