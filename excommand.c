#include "headers.h"
#include "myfunction.h"

void excommand(char **command, int num, int *numbg, char **bgcmds, int *bgpid)
{

    // for fg commands
    if (strcmp(*(command + num - 1), "&") != 0)
    {
        if (strcmp(*(command + 0), "echo") == 0)
            ex_echo(command, num);

        else if (strcmp(*(command + 0), "cd") == 0)
            ex_cd(command, num);

        else if (strcmp(*(command + 0), "repeat") == 0)
            ex_repeat(command, num, numbg, bgcmds, bgpid);

        else if (strcmp(*(command + 0), "ls") == 0)
            ex_ls(command, num);

        else if (strcmp(*(command + 0), "pwd") == 0)
        {
            char *dir = malloc(sizeof(char *) * 10000);
            if (getcwd(dir, 10000) == NULL)
            {
                throwerr("cannot get current directory");
            }

            printf("%s\n", dir);
        }

        else if (strcmp(*(command + 0), "pinfo") == 0)
            ex_pinfo(command, num);

        else if (strcmp(*(command + 0), "exit()") == 0)
        {
            run = 0;
            return;
        }

        else
            ex_sys(command, num);
    }
    else
    {
        ex_bg(command, num, numbg, bgcmds, bgpid);
    }
}
