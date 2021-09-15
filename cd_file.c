#include "headers.h"

void ex_cd(char **command, int num)
{
    char test[1000];
    if (num > 2)
    {
        perror(" cd : too many arguments");
        return;
    }
    if(num==1 || strcmp(*(command+1),"~")==0)
    {
        int x = chdir(home_dir);
        if (x == -1)
        {
            throwerr("cdeez nuts");
            return;
        }
    }
    else
    {

        int x = chdir(*(command+1));
        if (x == -1)
        {
            throwerr("cdeez nuts");
            return;
        }
    }
    return;
}