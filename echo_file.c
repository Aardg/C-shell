#include "headers.h"

void ex_echo(char **command, int num)
{
    for (int i = 1; i < num; i++)
    {
        printf("%s ", *(command + i));
    }
}