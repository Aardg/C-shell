#include "headers.h"
#include "myfunction.h"

void excommand(char **command, int num, int *numbg, char **bgcmds, int *bgpid)
{

    int rd_end, wr_end,pip=0,redirect_flag=0;
    rd_end = dup(STDIN_FILENO);
    wr_end = dup(STDOUT_FILENO);

    // check for pipes
    for (int i = 0; i < num; i++)
    {
        if (strcmp(*(command + i), "|") == 0)
        {
            pip=1;

            ex_pipe(command, num, numbg, bgcmds, bgpid, STDIN_FILENO, STDOUT_FILENO);
            return;
        }
        else if(strcmp(*(command + i), "<") == 0 || strcmp(*(command + i), ">") == 0 || strcmp(*(command + i), ">>")==0)
            redirect_flag=1;
    }
    // for fg commands
    if (pip == 0)
    {
        if (strcmp(*(command + num - 1), "&") != 0)
        {
            if(redirect_flag==1)
                ex_redirect(command,num,numbg, bgcmds, bgpid, STDIN_FILENO, STDOUT_FILENO);
            else if (strcmp(*(command + 0), "echo") == 0)
                ex_echo(command, num, STDIN_FILENO, STDOUT_FILENO);

            else if (strcmp(*(command + 0), "cd") == 0)
                ex_cd(command, num, STDIN_FILENO, STDOUT_FILENO);

            else if (strcmp(*(command + 0), "repeat") == 0)
                ex_repeat(command, num, numbg, bgcmds, bgpid, STDIN_FILENO, STDOUT_FILENO);

            else if (strcmp(*(command + 0), "ls") == 0)
                ex_ls(command, num, STDIN_FILENO, STDOUT_FILENO);

            else if (strcmp(*(command + 0), "jobs") == 0)
                ex_jobs(command, num, numbg, bgcmds, bgpid, STDIN_FILENO, STDOUT_FILENO);
            
             else if (strcmp(*(command + 0), "sig") == 0)
                ex_sig(command, num, numbg, bgcmds, bgpid, STDIN_FILENO, STDOUT_FILENO);

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
                ex_pinfo(command, num, STDIN_FILENO, STDOUT_FILENO);

            else if (strcmp(*(command + 0), "exit()") == 0)
            {
                run = 0;
                return;
            }

            else
                ex_sys(command, num, STDIN_FILENO, STDOUT_FILENO);
        }
        else
        {
            ex_bg(command, num, numbg, bgcmds, bgpid, STDIN_FILENO, STDOUT_FILENO);
        }
    }
    return;
}
