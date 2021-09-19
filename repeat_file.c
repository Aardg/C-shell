#include "myfunction.h"
#include "headers.h"

void ex_repeat(char **command, int num, int *numbg, char **bgcmds, int *bgpid)
{
    if(num<3)
    {
        throwerr("repeat: insufficient amount of argumnets provided");
        return;
    }

    int loop = atoi(*(command + 1));
    if(loop==0)
        return;
    char **repeated = (char **)malloc(sizeof(char *) * num);

    for(int i=2;i<num;i++)
    {
        *(repeated+i-2) = *(command + i);
    }

    for(int i=0;i<loop;i++)
    {
        excommand(command, num-2,numbg,bgcmds,bgpid);
    }
    
}