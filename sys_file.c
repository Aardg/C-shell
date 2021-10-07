#include "headers.h"
#include "myfunction.h"

void ex_sys(char **command, int num,int in, int out)
{

    int org_rd = dup(STDIN_FILENO);
    int org_wr = dup(STDOUT_FILENO);

    dup2(in,STDIN_FILENO);
    dup2(out,STDOUT_FILENO);

    int fl;
    // printf("in the sys file bginning %d",(num+5)*sizeof(char **));
    fflush(stdout);
    command = realloc(command, (num+5)*sizeof(char **));
    *(command+num)='\0';
    // printf("in the sys file after realoc");
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
        tt = execvp(*(command+0),command);
        if(tt==-1)
        {
            throwerr("mhl");
            return;
        }
    }
    else
    {
        wait(NULL);
    }
    dup2(org_rd,STDIN_FILENO);
    dup2(org_wr,STDOUT_FILENO);

    return;
}
