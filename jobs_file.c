#include "headers.h"

struct process
{
    char *stat;
    int num;
    char *name;
    int pid;
};
int comparator(const void *p, const void *q)
{
    return strcmp(((struct process *)p)->name, ((struct process *)q)->name);
}
void ex_jobs(char **command, int num, int *numbg, char **bgcmds, int *bgpid, int in, int out)
{
    int org_rd = dup(STDIN_FILENO);
    int org_wr = dup(STDOUT_FILENO);
    dup2(in, STDIN_FILENO);
    dup2(out, STDOUT_FILENO);

    int rflag = -1;
    int sflag = -1;
    int ef = -1;
    for (int i = 1; i < num; i++)
    {
        if ((*(command + i))[0] == '-')
        {
            for (int j = 1; j < strlen(*(command + i)); j++)
            {
                if ((*(command + i))[j] == 'r')
                    rflag = 1;
                else if ((*(command + i))[j] == 's')
                    sflag = 1;
                else
                    ef = 1;
            }
        }
        else
        {
            write(0, "unknown arguments\n", 18);
            return;
        }
        if (ef == 1)
        {
            write(0, "unknown arguments\n", 18);
            return;
        }
    }

    struct process arr[*numbg];
    int num_proc = 0;
    for (int i = 0; i < *numbg; i++)
    {
        if (*(bgpid + i) != 0)
        {
            arr[num_proc].num = i+1;
            arr[num_proc].name = *(bgcmds + i);
            arr[num_proc].pid = *(bgpid + i);

            char *stat_path = malloc(sizeof(char *) * 1000);
            char *exe_path = malloc(sizeof(char *) * 1000);

            if (stat_path == NULL || exe_path == NULL)
            {
                throwerr("malloc error ");
                return;
            }
            sprintf(stat_path, "/proc/%d/stat", *(bgpid + i));
            sprintf(exe_path, "/proc/%d/exe", *(bgpid + i));

            int fd = open(stat_path, O_RDONLY);
            if (fd == -1)
            {
                throwerr("Process with the given PID does not exist");
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
            if (*(*(sep_data + 2)) == 'R' || *(*(sep_data + 2)) == 'S')
                arr[num_proc].stat = "Running";
            else
                arr[num_proc].stat = "Stopped";

            // printf("aftstrcmp");
            // fflush(stdout);
            // printf("[%d] %s %s [%d]\n", arr[num_proc].num, arr[num_proc].stat, arr[num_proc].name, arr[num_proc].pid);
            num_proc += 1;
        }
    }
    qsort(arr, num_proc, sizeof(struct process), comparator);
    for (int i = 0; i < num_proc; i++)
    {

        if (num == 1)
            printf("[%d] %s %s [%d]\n", arr[i].num, arr[i].stat, arr[i].name, arr[i].pid);
        else
        {
            if (sflag == 1)
            {
                if (strcmp(arr[i].stat, "Stopped") == 0)
                    printf("[%d] %s %s [%d]\n", arr[i].num, arr[i].stat, arr[i].name, arr[i].pid);
            }

            if (rflag == 1)
            {
                if (strcmp(arr[i].stat, "Running") == 0)
                    printf("[%d] %s %s [%d]\n", arr[i].num, arr[i].stat, arr[i].name, arr[i].pid);
            }
        }
    }

    dup2(org_rd, STDIN_FILENO);
    dup2(org_wr, STDOUT_FILENO);
}