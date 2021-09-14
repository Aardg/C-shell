#include "headers.h"


void prompt(int *run)
{
    int flag;
    char* h_name,u_name;
    long unsigned int lim = 10000;
    char* comm;
    char **sep_comm;
    char **trim_comm;
    struct passwd *gu_name=getpwuid(geteuid());

    comm = (char *)malloc(10000*sizeof(char));
    sep_comm = (char **)malloc(1000*sizeof(char*));
    trim_comm = (char **)malloc(1000*sizeof(char*));
    if(gu_name==NULL)
    {
        throwerr("getpwid failed");
    }
    h_name =(char *)malloc(10000*sizeof(char));
    flag = gethostname(h_name,10000);
    if(flag==-1)
    {
        throwerr("host name had problems");
    }
    h_name=(char *) realloc(h_name,sizeof(char)*(strlen(h_name)+2));
    printf("\033[0;36m");
	printf("%s@%s > ",gu_name->pw_name,h_name);
	printf("\033[0m");
    getline(&comm,&lim,stdin);
    *(comm + strlen(comm)-1)='\0';
    char *token = strtok(comm,";");
    int num_commands=0,maxcom = 1000;
    while (token!=NULL)
    {
        if(num_commands==maxcom)
        {
            maxcom+=1000;
            sep_comm = (char **)realloc(sep_comm,maxcom*sizeof(char *));
        }
        *(sep_comm+num_commands)=token;
        token = strtok(NULL,";"); 
        num_commands+=1;
    }
    for(int j=0;j<num_commands;j++)
    {
        printf("%s \n its components are :  \n",*(sep_comm+j));
        char *token = strtok(sep_comm," \t");
        int sub_commands=0,maxcom = 1000;
        while(token!=NULL)
        {

        }
    }
    


    
}