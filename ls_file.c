#include "myfunction.h"
#include "headers.h"

void ex_ls(char **command, int num)
{
    char month[][5] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int lf = 0, af = 0, ef = 0, num_dir = 0;
    char **args = (char **)malloc(1000 * sizeof(char *));
    for (int i = 1; i < num; i++)
    {
        if ((*(command + i))[0] == '-')
        {
            for (int j = 1; j < strlen(*(command + i)); j++)
            {
                if ((*(command + i))[j] == 'l')
                    lf = 1;
                else if ((*(command + i))[j] == 'a')
                    af = 1;
                else
                    ef = 1;
            }
        }
        else
        {
            num_dir += 1;
            *(args + num_dir - 1) = (char *)malloc(strlen(*(command + i)) * sizeof(char));
            strcpy(*(args + num_dir - 1), *(command + i));
        }
        if (ef == 1)
        {
            throwerr("ls : invalid flag provided");
            return;
        }
    }
    //add current directory to arguments
    if (num_dir == 0)
    {
        num_dir += 1;
        *(args + num_dir - 1) = (char *)malloc(2 * sizeof(char));
        strcpy(*(args + num_dir - 1), ".");
    }
    for (int j = 0; j < num_dir; j++)
    {
        // ls of other directories
        // strcat(entry,"%d,%d,%d,%s\n", lf,af,ef,*(args + j));
        char *path = malloc(sizeof(char *) * 1000);
        if ((*(args + j))[0] == '~')
        {
            strcpy(path, home_dir);
            for (int i = 0; i < strlen(*(args + j)) - 1; i++)
            {
                *(path + home_dirsz + i) = (*(args + j))[i + 1];
            }
        }
        else
        {
            strcpy(path, *(args + j));
        }

        struct stat s, t;

        if (stat(path, &s) == 0)
        {
            if (S_ISDIR(s.st_mode))
            {
                DIR *dir = opendir(path);

                if (dir == NULL)
                {
                    throwerr("opendir");
                }

                struct dirent *content;
                while ((content = readdir(dir)) != NULL)
                {
                    char fname[1000] = "";
                    sprintf(fname,"%s/%s",path,content->d_name);
                    if (stat(fname, &t) == 0)
                    {
                        if ((*(content->d_name) != '.' && af == 0) || af == 1)
                        {

                            struct tm dt;
                            dt = *(gmtime(&t.st_ctime));

                            char entry[1000] = "";
                            char details[1000];
                            if (lf == 1)
                            {
                                if (S_ISDIR(t.st_mode))
                                    strcat(entry, "d");
                                else
                                    strcat(entry, "-");

                                if (t.st_mode & S_IRUSR)
                                    strcat(entry, "r");
                                else
                                    strcat(entry, "-");

                                if (t.st_mode & S_IWUSR)
                                    strcat(entry, "w");
                                else
                                    strcat(entry, "-");

                                if (t.st_mode & S_IXUSR)
                                    strcat(entry, "x");
                                else
                                    strcat(entry, "-");

                                if (t.st_mode & S_IRGRP)
                                    strcat(entry, "r");
                                else
                                    strcat(entry, "-");

                                if (t.st_mode & S_IWGRP)
                                    strcat(entry, "w");
                                else
                                    strcat(entry, "-");

                                if (t.st_mode & S_IXGRP)
                                    strcat(entry, "x");
                                else
                                    strcat(entry, "-");

                                if (t.st_mode & S_IROTH)
                                    strcat(entry, "r");
                                else
                                    strcat(entry, "-");

                                if (t.st_mode & S_IWOTH)
                                    strcat(entry, "w");
                                else
                                    strcat(entry, "-");

                                if (t.st_mode & S_IXOTH)
                                    strcat(entry, "x  ");
                                else
                                    strcat(entry, "-  ");

                                sprintf(details, "%ld  %s  %s %ld", t.st_nlink, getpwuid(t.st_uid)->pw_name, getgrgid(t.st_gid)->gr_name, t.st_size);
                                strcat(entry, details);
                                dt = *(gmtime(&t.st_ctime));
                                sprintf(details, " %s %d %d:%d", month[dt.tm_mon], dt.tm_mday, dt.tm_hour, dt.tm_min);  
                                strcat(entry, details);
                            }
                            strcat(entry, content->d_name);
                            printf("%s \n",entry);
                        }
                    }
                }
                closedir(dir);
            }
            else
            {

                struct tm dt;
                dt = *(gmtime(&s.st_ctime));

                char entry[1000] = "";
                char details[1000];
                if (lf == 1)
                {
                    if (S_ISDIR(s.st_mode))
                        strcat(entry, "d");
                    else
                        strcat(entry, "-");

                    if (s.st_mode & S_IRUSR)
                        strcat(entry, "r");
                    else
                        strcat(entry, "-");

                    if (s.st_mode & S_IWUSR)
                        strcat(entry, "w");
                    else
                        strcat(entry, "-");

                    if (s.st_mode & S_IXUSR)
                        strcat(entry, "x");
                    else
                        strcat(entry, "-");

                    if (s.st_mode & S_IRGRP)
                        strcat(entry, "r");
                    else
                        strcat(entry, "-");

                    if (s.st_mode & S_IWGRP)
                        strcat(entry, "w");
                    else
                        strcat(entry, "-");

                    if (s.st_mode & S_IXGRP)
                        strcat(entry, "x");
                    else
                        strcat(entry, "-");

                    if (s.st_mode & S_IROTH)
                        strcat(entry, "r");
                    else
                        strcat(entry, "-");

                    if (s.st_mode & S_IWOTH)
                        strcat(entry, "w");
                    else
                        strcat(entry, "-");

                    if (s.st_mode & S_IXOTH)
                        strcat(entry, "x  ");
                    else
                        strcat(entry, "-  ");

                    sprintf(details, "%ld  %s  %s %ld", s.st_nlink, getpwuid(s.st_uid)->pw_name, getgrgid(s.st_gid)->gr_name, s.st_size);
                    strcat(entry, details);
                    dt = *(gmtime(&s.st_ctime));
                    sprintf(details, " %s %d %d:%d ", month[dt.tm_mon], dt.tm_mday, dt.tm_hour, dt.tm_min);
                    strcat(entry, details);
                }
                strcat(entry,path);
                printf("%s \n",entry);
            }
        }

        else
        {
            throwerr("ls : ");
        }
    }
}