#include "headers.h"
void ex_sig(char **command, int num, int *numbg, char **bgcmds, int *bgpid,int in, int out)
{
    if(num!=3)
    {
        throwerr("bad number of arguments");
        return;
    }
    int sig = atoi(*(command+2));
    int comm_num = atoi(*(command+1));

    if(comm_num>*numbg)
    {
        throwerr("invalid command number");
        return;
    }
    int pid = *(bgpid+comm_num-1);
    if(pid==0)
    {
        throwerr("invalid command number");
        return;
    }
    kill(pid,sig);
    return;

}