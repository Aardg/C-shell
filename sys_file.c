#include "headers.h"
#include "myfunction.h"

void ex_sys(char **command, int num)
{
    int fl;
    command = (char **)realloc(command, (num+5) * sizeof(char *));
    *(command+num)='\0';
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
    return;
}
