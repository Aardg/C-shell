#include "headers.h"

void ex_bg(char **command, int num, int *numbg, char **bgcmds, int *bgpid)
{

    num = num - 1;
    *(command + num) = '\0';

    int pid = getpid();
    int pgid = getpgid(pid);
    if (pgid == -1)
        throwerr("Internal Error occured");

    int tine = fork();
    int eid;
    if (tine < 0)
        throwerr("forking error");
    if (tine == 0)
    {
        setpgid(tine, tine);

        eid = execvp(*(command), command);
        if (eid == -1)
            throwerr("mhl");
    }
    else if (tine > 0)
    {

        tcsetpgrp(STDIN_FILENO, pgid);

        setpgid(tine, tine);
        printf("[%d] %d \n", *(numbg) + 1, tine);


        int free;
        for (free = 0; free <= *(numbg); free++)
        {
    
            if (*(bgpid + free) == 0)
            {
                *(bgpid + free) = tine;

                break;
            }
        }
    
        *(bgcmds + free) = malloc(100 * sizeof(char *));
        strcpy(*(bgcmds + free), *(command + 0));
        if (free == (*numbg))
        {
            
            (*numbg) = (*numbg)+1;
        }
    }
    return;
}