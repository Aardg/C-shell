#include "headers.h"

void ex_pipe(char **command, int num, int *numbg, char **bgcmds, int *bgpid,int in, int out)
{
    // printf("************************n epipe\n");
    int org_rd = dup(STDIN_FILENO);
    int org_wr = dup(STDOUT_FILENO);

    dup2(in,STDIN_FILENO);
    dup2(out,STDOUT_FILENO);
    int pipe_pos;
    char **f_command = malloc(1000*sizeof(char **));

    for(int i=0;i<num;i++)
    {
        *(f_command+i) = malloc(strlen(*(command+i))*sizeof(char *));
        strcpy(*(f_command+i),*(command+i));
        if(strcmp(*(command+i),"|")==0)
        {
            pipe_pos=i;
            break;
        }
    }
    *(f_command+pipe_pos)=NULL;
    // int i=0;
    // while(*(f_command+i)!=NULL)
    // {
    //     printf("fcomm %s\n",*(f_command+i));
    //     i+=1;    
    // }
    int fildes[2],tine,pip_rec=0,flag;
    flag = pipe(fildes);
    if(flag == -1)
        throwerr("pipe ");

    tine = fork();
    if(tine<0)
        throwerr("fork");
    else if(tine==0)
    {
        close(fildes[0]);
        ex_redirect(f_command,pipe_pos,numbg,bgcmds,bgpid,in,fildes[1]);

        close(fildes[1]);
        dup2(org_rd,STDIN_FILENO);
        dup2(org_wr,STDOUT_FILENO);
        close(org_wr);
        close(org_rd);
        exit(0);
    }
    else if(tine>0)
    {
        close(fildes[1]);
        waitpid(tine,NULL,WUNTRACED);
        pip_rec=0;
        int len=0;
        for(int i=pipe_pos+1;i<num;i++)
        {
            if(strcmp(*(command+i),"|")==0)
            {
                ex_pipe(command+pipe_pos+1,num-pipe_pos-1,numbg,bgcmds,bgpid,fildes[0],out);
                pip_rec=1;
                break;
            }
            len++;
        }
        if(pip_rec==0)
            ex_redirect(command + pipe_pos+1,len,numbg,bgcmds,bgpid,fildes[0],out);
        close(fildes[0]);
        dup2(org_rd,STDIN_FILENO);
        dup2(org_wr,STDOUT_FILENO);
        close(org_wr);
        close(org_rd);
        return;
    }
    return;
}