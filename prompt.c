#include "headers.h"

void prompt()
{
    int flag;
    int run;
    char *h_name, u_name;
    long unsigned int lim = 10000;
    char *comm;
    char **sep_comm;
    char relative[10000];
    char curdir_name[10000];

    // get user name
    struct passwd *gu_name = getpwuid(geteuid());
    if (gu_name == NULL)
    {
        throwerr("getpwid failed");
    }
    h_name = (char *)malloc(10000 * sizeof(char));

    //get host name
    flag = gethostname(h_name, 10000);
    if (flag == -1)
    {
        throwerr("host name had problems");
    }
    h_name = (char *)realloc(h_name, sizeof(char) * (strlen(h_name) + 2));

    // get home directory
    if (getcwd(home_dir, 10000) == NULL)
    {
        throwerr("cannot get home directory");
    }
    // if (!(strlen(home_dir) == 1 && home_dir[0] == '/'))
    // {
    //     home_dir[strlen(home_dir) + 1] = '\0';
    //     home_dir[strlen(home_dir)] = '/';
    // }
    home_dirsz = strlen(home_dir);
    strcpy(curdir_name, home_dir);
    run = 1;
    while (run)
    {

        // print username@host
        printf("\033[0;36m");
        printf("%s@%s : ", gu_name->pw_name, h_name);
        printf("\033[0m");
        if(getcwd(curdir_name,1000)==NULL)
        {
            throwerr("directory nhi mili");
        }
        //printing current directory
        if (strcmp(curdir_name,home_dir) == 0)
            printf("~ $ ");
        else
        {
            int rel = 0;
            for (rel = 0; rel < home_dirsz; rel++)
            {
                if (curdir_name[rel] != home_dir[rel])
                {
                    break;
                }
            }
            if (rel == home_dirsz)
            {
                printf(" ~ ");
                for (int i = home_dirsz; i < strlen(curdir_name); i++)
                    printf("%c", curdir_name[i]);
                printf(" $ ");
            }
            else
            {
                printf("%s $ ", curdir_name);
            }
        }

        // input command
        comm = (char *)malloc(10000 * sizeof(char));
        sep_comm = (char **)malloc(1000 * sizeof(char *));
        getline(&comm, &lim, stdin);
        *(comm + strlen(comm) - 1) = '\0';
        char *token = strtok(comm, ";");
        int num_commands = 0, maxcom = 1000;

        //breaking compound commands into its individual commands
        while (token != NULL)
        {
            if (num_commands == maxcom)
            {
                maxcom += 1000;
                sep_comm = (char **)realloc(sep_comm, maxcom * sizeof(char *));
            }
            *(sep_comm + num_commands) = token;
            token = strtok(NULL, ";");
            num_commands += 1;
        }

        //tokenizing to account for extra spaces

        for (int j = 0; j < num_commands; j++)
        {
            char **trim_comm;
            trim_comm = (char **)malloc(1000 * sizeof(char *));
            char *token = strtok(*(sep_comm + j), " \t");
            int sub_commands = 0, maxcom = 1000;
            while (token != NULL)
            {
                if (sub_commands == maxcom)
                {
                    maxcom += 1000;
                    sep_comm = (char **)realloc(trim_comm, maxcom * sizeof(char *));
                }
                *(trim_comm + sub_commands) = token;
                token = strtok(NULL, " \t");
                sub_commands += 1;
            }

            excommand(trim_comm, sub_commands);

            printf("\n");
            free(trim_comm);
        }
        free(sep_comm);
    }
}