#include "myfunction.h"
#include "headers.h"

void ex_pinfo(char **command, int num,int in, int out)
{
    int org_rd = dup(STDIN_FILENO);
    int org_wr = dup(STDOUT_FILENO);

    dup2(in,STDIN_FILENO);
    dup2(out,STDOUT_FILENO);

    int fg_flag = 0;
    if (num > 2)
    {
        printf("pinfo only takes 1 argument");
        return;
    }
    else
    {
        char *stat_path = malloc(sizeof(char *) * 1000);
        char *exe_path = malloc(sizeof(char *) * 1000);

        if (stat_path == NULL || exe_path == NULL)
        {
            throwerr("malloc error ");
            return;
        }
        if (num == 1)
        {
            int pid = getpid();
            if(getpgid(pid) == tcgetpgrp(STDIN_FILENO))
                fg_flag=1;
            if (pid == -1)
            {
                throwerr("getpid failed ");
                return;
            }
            printf("pid -- %d\n", pid);
            sprintf(stat_path, "/proc/%d/stat", pid);
            sprintf(exe_path, "/proc/%d/exe", pid);
        }
        else
        {
            printf("pid -- %s\n", *(command + 1));
            int pid = atoi(*(command + 1));
            if(getpgid(pid) == tcgetpgrp(STDIN_FILENO))
                fg_flag=1;
            sprintf(stat_path, "/proc/%s/stat", *(command + 1));
            sprintf(exe_path, "/proc/%s/exe", *(command + 1));
        }

        int fd = open(stat_path, O_RDONLY);
        if (fd == -1)
        {
            printf("Process with the given PID does not exist");
            return;
        }
        char *data = malloc(sizeof(char *) * 2050);
        read(fd, data, 2048);

        char **sep_data = malloc(sizeof(char **) * 1000);
        char *token = strtok(data, " ");
        int data_num = 0;
        while (token != NULL)
        {
            *(sep_data + data_num) = token;
            token = strtok(NULL, " ");
            data_num += 1;
        }
        printf("Process Status -- %s", *(sep_data + 2));
        if(fg_flag==1)
            printf("+\n");
        else
            printf("\n");
        printf("memory -- %s\n", *(sep_data + 22));
        int l = readlink(exe_path, data, 1000);
        if (l < 0)
        {
            perror("error in opening exe file of given pid\n");
            return;
        }
        data[l] = '\0';
        printf("Executable Path -- %s\n",data);

        free(stat_path);
        free(exe_path);
        free(sep_data);
    }
    dup2(org_rd,STDIN_FILENO);
    dup2(org_wr,STDOUT_FILENO);
}