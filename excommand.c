#include "headers.h"
#include "myfunction.h"


void excommand(char **command ,int num)
{
    printf("in function \n");
    for(int i=0;i<num;i++)
    {
        printf("%s",*(command+i));
    }
}

