#include "headers.h"
#include "myfunction.h"

void ex_redirect(char **command, int num, int *numbg, char **bgcmds, int *bgpid, int in, int out)
{
    // printf("*********************in redi\n");
    // int i=0;
    // while(*(command+i)!=NULL)
    // {
    //     printf("redcomm %s\n",*(command+i));
    //     i+=1;
    // }

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
    // printf("%d %d",our_inp,our_op);
    // printf("%s",*(sep_commands + 0));
    if (strcmp(*(sep_commands + 0), "echo") == 0)
        ex_echo(sep_commands, k, our_inp, our_op);

    else if (strcmp(*(sep_commands + 0), "cd") == 0)
        ex_cd(sep_commands, k, our_inp, our_op);

    else if (strcmp(*(sep_commands + 0), "repeat") == 0)
        ex_repeat(sep_commands, k, numbg, bgcmds, bgpid, our_inp, our_op);
    
    else if (strcmp(*(sep_commands + 0), "jobs") == 0)
        ex_jobs(sep_commands, k, numbg, bgcmds, bgpid, our_inp, our_op);
    
     else if (strcmp(*(sep_commands + 0), "sig") == 0)
        ex_sig(sep_commands, k, numbg, bgcmds, bgpid, our_inp, our_op);

    else if (strcmp(*(sep_commands + 0), "ls") == 0)
        ex_ls(sep_commands, k, our_inp, our_op);

    else if (strcmp(*(sep_commands + 0), "pwd") == 0)
    {
        if (k > 1)
        {
            throwerr("too many args");
        }
        else
        {
            char *dir = malloc(sizeof(char *) * 10000);
            if (getcwd(dir, 10000) == NULL)
            {
                throwerr("cannot get current directory");
            }

            printf("%s\n", dir);
        }
    }

    else if (strcmp(*(sep_commands + 0), "pinfo") == 0)
        ex_pinfo(sep_commands, k, our_inp, our_op);

    else if (strcmp(*(sep_commands + 0), "exit()") == 0)
    {
        run = 0;
        return;
    }

    else
        ex_sys(sep_commands, k, our_inp, our_op);

    dup2(org_rd, STDIN_FILENO);

    dup2(org_wr, STDOUT_FILENO);
    close(in_fd);

    close(out_fd);

    close(org_wr);
    close(org_rd);
}