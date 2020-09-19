#include "file.h"
#define rep(i,a,b) for(int i=a;i<b;i++)

const char *separator= " ";
const int MAX_CMD = 16;
int argCount(char ** args)
{
    int count=0;
    while(args[count++]);
    count--;
    return count;
}
char ** argumentize(char *cmd)
{
	int count=0;
	char *str = strdup(cmd);
    char **args = malloc(MAX_CMD * sizeof(char *));
    

    args[count++]=strtok(str,separator);

    while(args[count-1]!=0)
        args[count++]=strtok(NULL,separator);

    args[count++]=NULL;
    
    return args;
}


