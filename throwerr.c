#include "headers.h"

void throwerr(char err[])
{
    perror(err);
    return;
}