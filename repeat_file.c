#include "myfunction.h"
#include "headers.h"

void ex_repeat(char **command, int num, int *numbg, char **bgcmds, int *bgpid, int in, int out)
{
    int org_rd = dup(STDIN_FILENO);
    int org_wr = dup(STDOUT_FILENO);

    dup2(in,STDIN_FILENO);
    dup2(out,STDOUT_FILENO);
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
        excommand(repeated, num-2,numbg,bgcmds,bgpid);
    }

    dup2(org_rd,STDIN_FILENO);
    dup2(org_wr,STDOUT_FILENO);
    
}