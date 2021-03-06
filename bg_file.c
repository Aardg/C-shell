#include "headers.h"

void ex_bg(char **command, int num, int *numbg, char **bgcmds, int *bgpid,int in, int out)
{

    num = num - 1;
    *(command + num) = '\0';

    int pid = getpid();
    int pgid = getpgid(pid);
    if (pgid == -1)
        throwerr("Internal Error occured");
    int out_fd = -2;
    int in_fd = -2;
    int app = 0, org_rd, org_wr, flag, inp_flg = 0, op_flg = 0, ap_flg = 0, our_inp = 0, our_op = 1;
    char **sep_commands = malloc(num * sizeof(char **));
    char *inpfile, *opfile;

    org_rd = dup(STDIN_FILENO);
    org_wr = dup(STDOUT_FILENO);

    if (in != 0)
        flag = dup2(in, STDIN_FILENO);

    if (out != 1)
        flag = dup2(out, STDOUT_FILENO);

    int j = 0, k = 0;
    while (j < num && strcmp(*(command + j), "<") != 0)
    {
        // printf("command is  %s \n", *(command + j));
        fflush(stdout);

        *(sep_commands + k) = malloc(strlen(*(command + j)) * sizeof(char *));
        strcpy(*(sep_commands + k), *(command + j));
        k++;
        j++;
    }
    if (j < num && strcmp(*(command + j), "<") == 0)
    {
        inp_flg = 1;
    }
    *(sep_commands + k) = NULL;
    // printf("se[ comm %s \n", *(sep_commands));
    inpfile = malloc(10000 * sizeof(char *));
    opfile = malloc(10000 * sizeof(char *));
    if (inp_flg == 1)
    {
        // printf("input flg\n");
        for (j = j + 1; j < num; j++)
        {
            if (strcmp(*(command + j), ">") == 0)
            {
                op_flg = 1;
                break;
            }
            else if (strcmp(*(command + j), ">>") == 0)
            {
                op_flg = 1;
                ap_flg = 1;
                break;
            }
            else
            {
                strcat(inpfile, *(command + j));
                strcat(inpfile, " ");
            }
            *(inpfile + (strlen(inpfile) - 1)) = '\0';
        }
        if (op_flg == 1)
        {
            // printf("i and o");

            for (j = j + 1; j < num; j++)
            {
                strcat(opfile, *(command + j));
                strcat(opfile, " ");
            }
            *(opfile + (strlen(opfile) - 1)) = '\0';
            // printf("%s",opfile);
        }
        in_fd = open(inpfile, O_RDONLY);
        if (in_fd == -1)
        {
            throwerr("no such file exists");
            if (in != STDIN_FILENO)
                dup2(org_rd, STDIN_FILENO);
            if (out != STDOUT_FILENO)
                dup2(org_wr, STDOUT_FILENO);

            close(org_wr);
            close(org_rd);
            return;
        }
        flag = dup2(in_fd, STDIN_FILENO);
        if (flag == -1)
        {
            throwerr("dup2 failed");
            return;
        }
        our_inp = in_fd;
    }
    else
    {
        k = 0;
        j = 0;
        while (j < num && (strcmp(*(command + j), ">") != 0 && strcmp(*(command + j), ">>") != 0))
        {
            k++;
            j++;
        }
        if (j < num && strcmp(*(command + j), ">") == 0)
        {
            op_flg = 1;
        }
        else if (j < num && strcmp(*(command + j), ">>") == 0)
        {
            op_flg = 1;
            ap_flg = 1;
        }
        *(sep_commands + k) = NULL;
        if (op_flg == 1)
        {
            for (j = j + 1; j < num; j++)
            {
                strcat(opfile, *(command + j));
                strcat(opfile, " ");
            }
            *(opfile + (strlen(opfile) - 1)) = '\0';
        }
    }
    umask(0000);
    // printf("%d,%d,%d",op_flg,ap_flg,strlen(opfile));
    if (op_flg == 1 && ap_flg == 0 && strlen(opfile) != 0)
    {
        out_fd = open(opfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // printf("aarha hai");
        if (out_fd == -1)
            throwerr("opening failed");
    }
    else if (op_flg == 1 && ap_flg == 1 && strlen(opfile) != 0)
    {
        struct stat s;
        flag = stat(opfile, &s);
        if (flag == -1)
        {
            out_fd = open(opfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_fd == -1)
                throwerr("opening failed");
        }
        else
        {
            out_fd = open(opfile, O_WRONLY | O_APPEND);
            if (out_fd == -1)
                throwerr("opening failed");
        }
    }

    if (out_fd != -2)
    {
        // printf("here!@!");
        flag = dup2(out_fd, STDOUT_FILENO);
        if (flag == -1)
            throwerr("dup2 system call failed");
        our_op = out_fd;
    }
    int tine = fork();
    int eid;
    if (tine < 0)
        throwerr("forking error");
    if (tine == 0)
    {
        setpgid(tine, tine);

        eid = execvp(*(sep_commands), sep_commands);
        if (eid == -1)
            throwerr("mhl");
    }
    else if (tine > 0)
    {

        tcsetpgrp(STDIN_FILENO, pgid);

        setpgid(tine, tine);
        printf("[%d] %d \n", *(numbg) + 1, tine);


        int free;
        for (free = 0; free <= *(numbg); free++)
        {
    
            if (*(bgpid + free) == 0)
            {
                *(bgpid + free) = tine;

                break;
            }
        }
    
        *(bgcmds + free) = malloc(100 * sizeof(char *));
        strcpy(*(bgcmds + free), *(sep_commands + 0));
        if (free == (*numbg))
        {
            
            (*numbg) = (*numbg)+1;
        }
    }
    dup2(org_rd,STDIN_FILENO);
    dup2(org_wr,STDOUT_FILENO);
    return;
}