#include "headers.h"

void throwerr(char err[])
{
    perror(err);
    exit(1);

}