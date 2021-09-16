#ifndef __MYFUNCTIONS_H
#define __MYFUNCTIONS_H

void prompt();
void throwerr();
void excommand(char **command, int num);
void ex_echo(char **command, int num);
void ex_cd(char **command, int num);
void ex_repeat(char **command, int num);
void ex_ls(char **command, int num);

char home_dir[10000];
int home_dirsz;
int run;

char prev_dir[10000];
#endif