#include "headers.h"
#include "myfunction.h"

void excommand(char **command, int num)
{

    // echo
    if (strcmp(*(command + 0), "echo") == 0)
        ex_echo(command, num);

    if (strcmp(*(command + 0), "cd") == 0)
        ex_cd(command, num);

    if (strcmp(*(command + 0), "pwd") == 0)
    {
        char cur_dir[10000];

        if (getcwd(cur_dir, 10000) == NULL)
        {
            throwerr("cannot get home directory");
        }

        printf("%s\n", cur_dir);
    }
    if (strcmp(*(command + 0), "repeat") == 0)
        ex_repeat(command, num);

    if (strcmp(*(command + 0), "ls") == 0)
        ex_ls(command, num);

    if (strcmp(*(command + 0), "exit()") == 0)
    {
        printf("exiting myshell");
        run=0;
    }
}
