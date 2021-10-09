#include "headers.h"
#include "myfunction.h"

void ex_sys(char **command, int num,int in, int out)
{

    int org_rd = dup(STDIN_FILENO);
    int org_wr = dup(STDOUT_FILENO);

    dup2(in,STDIN_FILENO);
    dup2(out,STDOUT_FILENO);

    int fl,flag;
    fflush(stdout);
    command = realloc(command, (num+5)*sizeof(char **));
    *(command+num)='\0';
    fflush(stdout);
    fl = fork();
    if(fl==-1)
    {
        throwerr("fork : ");
        return;
    }
    if(fl==0)
    {
        int tt;
        tt=setpgid(0,0);
        if(tt==-1)
        {
            throwerr("setpgid");
            return;
        }
        signal(SIGINT,SIG_DFL);
		signal(SIGTSTP,SIG_DFL);
        tt = execvp(*(command+0),command);
        if(tt==-1)
        {
            throwerr("mhl");
            return;
        }
    }
    else
    {
        int tt;
        tt=setpgid(fl,fl);
        if(tt==-1)
        {
            throwerr("setpgid");
            return;
        }
        signal(SIGTTOU,SIG_IGN);
        signal(SIGTTOU,SIG_IGN);
		tcsetpgrp(STDIN_FILENO,fl);
		signal(SIGTTOU,SIG_DFL);
		kill(fl,SIGCONT);
        wait(NULL);
    }
    dup2(org_rd,STDIN_FILENO);
    dup2(org_wr,STDOUT_FILENO);

    return;
}
