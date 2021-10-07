#include "headers.h"

void ex_cd(char **command, int num,int in, int out )
{
    char test[1000];
    if (num > 2)
    {
        perror(" cd : too many arguments");
        return;
    }
    if (num == 1 || strcmp(*(command + 1), "~") == 0)
    {
        char cur_dir[10000];
        if (getcwd(cur_dir, 10000) == NULL)
        {
            throwerr("cannot get current directory");
        }
        strcpy(prev_dir, cur_dir);
        int x = chdir(home_dir);
        if (x == -1)
        {
            throwerr("cd : ");
            return;
        }
    }
    else if (strcmp(*(command + 1), "-") == 0)
    {
        char cur_dir[10000];
        if (getcwd(cur_dir, 10000) == NULL)
        {
            throwerr("cannot get current directory");
        }
        
        int x = chdir(prev_dir);
        if (x == -1)
        {
            throwerr("cd : ");
            return;
        }
        strcpy(prev_dir, cur_dir);

    }
    else
    {
        char cur_dir[10000];
        if (getcwd(cur_dir, 10000) == NULL)
        {
            throwerr("cannot get current directory");
        }
        if (*(command + 1)[0] == '~')
        {

            char *finpath = (char *)malloc(1000 * sizeof(char));

            finpath = strcpy(finpath, home_dir);
            *(finpath + home_dirsz) = '/';
            for (int i = 1; i < strlen(*(command + 1)); i++)
            {
                *(finpath + home_dirsz + i) = (*(command + 1))[i];
            }

            int x = chdir(finpath);
            if (x == -1)
            {
                throwerr("cd");
                return;
            }
            return;
        }

        int x = chdir(*(command + 1));
        if (x == -1)
        {
            throwerr("cd");
            return;
        }
        strcpy(prev_dir, cur_dir);
    }
    return;
}