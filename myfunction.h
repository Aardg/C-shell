#ifndef __MYFUNCTIONS_H
#define __MYFUNCTIONS_H

void prompt();
void throwerr();
void excommand(char **command, int num, int *numbg, char **bgcmds, int *bgpid);
void ex_echo(char **command, int num,int in, int out);
void ex_cd(char **command, int num,int in, int out);
void ex_repeat(char **command, int num, int *numbg, char **bgcmds, int *bgpid,int in, int out);
void ex_ls(char **command, int num,int in, int out);
void ex_sys(char **command, int num,int in, int out);
void ex_pinfo(char **command, int num,int in, int out);
void ex_bg(char **command, int num, int *numbg, char **bgcmds, int *bgpid,int in, int out);
void ex_pipe(char **command, int num, int *numbg, char **bgcmds, int *bgpid,int in, int out);
void ex_redirect(char **command, int num, int *numbg, char **bgcmds, int *bgpid,int in, int out);


// global variables
char home_dir[10000];
int home_dirsz;
int run;
char prev_dir[10000];

#endif