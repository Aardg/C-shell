#include "headers.h"

void ex_echo(char **command, int num,int in, int out)
{
    int org_rd = dup(STDIN_FILENO);
    int org_wr = dup(STDOUT_FILENO);

    dup2(in,STDIN_FILENO);
    dup2(out,STDOUT_FILENO);

    for (int i = 1; i < num; i++)
    {
        printf("%s ", *(command + i));
    }
    printf("\n");
    dup2(org_rd,STDIN_FILENO);
    dup2(org_wr,STDOUT_FILENO);
}