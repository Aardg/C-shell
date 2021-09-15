#include "headers.h"
#include "myfunction.h"

void excommand(char **command, int num)
{

    // echo
    if (strcmp(*(command + 0), "echo") == 0)
        ex_echo(command, num);

    if (strcmp(*(command + 0), "cd") == 0)
        ex_cd(command, num);
}
