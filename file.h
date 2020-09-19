#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<sys/utsname.h>
#include<fcntl.h>
#include<signal.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

char ** argumentize(char * cmd);
int argCount(char ** args);

//functions in builtin_pk_ls.c
char * formatDate(char *str,time_t val);
int cmd_pk_ls_l(char *path);
int cmd_pk_ls_l_a(char *path);
int cmd_pk_ls(char *path);
int cmd_pk_ls_a(char *path);
int print_pk_ls_l(char *path,char *fileName);


//functions in commandParser.c
char * parseCommand(char * cmd);

//fuctions in display.c
char * dirName();
void display();

//functions in execCmd.c
int findCmdNo(char *cmd);
int exec_pk_cd(char *cmd);
char **input();
int exec_pk_echo(char *cmd);
int exec_pk_ls(char *cmd);
int exec_pk_pwd();
int exec_pk_pinfo(char *cmd);
int checkBackgroud();
int exec_pk_clock(char *cmd);
int launch_cmd(char *cmd);
int execCmd(char *cmd);

//functions in input.c

//fuctions in lineParser.c
char ** tokanize(char * ptr);

//functions in pinfo.c
int exec_pinfo(int pid);

//functions in signal.c
void CtrlCHandler(int sig_num);
void CtrlZHandler(int sig_num);

//functions in exec_reminder.c
int exec_reminder(char *cmd);

//functions in redirect.c
char* checkInputRedirection(char *cmd);
char* checkOutputRedirection(char *cmd);
char* checkAppendRedirection(char *cmd);

//functions in pipe.c
int pipeExec(char *cmd);




//some interfile variables
pid_t CURR_FOREGROUND;
char * CURR_FOREGROUND_NAME;
