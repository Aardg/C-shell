#include "headers.h"
#include "myfunction.h"

int main()
{
    int *run;
    run=(int *)malloc(sizeof(int));
    *run=1;
    while(*run)
    {
        prompt(run);
    }
}