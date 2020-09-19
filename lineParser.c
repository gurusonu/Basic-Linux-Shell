#include "file.h"
#define rep1(i,a,b) for(i=a;i<b;i++)
const char *sep = ";\n";
char ** tokanize(char * ptr)
{
    int MAX_CMD= 16;
    char *str=strdup(ptr);
    char *tok;
    char **cmd=malloc(MAX_CMD*sizeof(char *));

    int count=0;
    cmd[count++]=strtok(str,sep);
    while(cmd[count-1]!=0)
        cmd[count++] = strtok(NULL,sep);
    cmd[count++] = NULL;
    return cmd;
}
