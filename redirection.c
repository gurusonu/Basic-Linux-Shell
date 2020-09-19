#include "file.h"
#define repx(i,a,b) for(int i=a;i<b;i++)

void truncateCommand(char *cmd,int index)
{
    int n=0,m=0,xx;
    int len=strlen(cmd);

    char ** argv=argumentize(cmd);
    int argc=argCount(argv);
    int i;
    for(i=0;i<index;i++)
    {
        n++;
        n=n+strlen(argv[i]);
    }
    m=strlen(argv[index])+strlen(argv[index+1]);
    m+=1;
    for(i=n;i<len-m;i++)
        cmd[i-1]=cmd[i+m];
    cmd[i]='\0';

}
char* checkInputRedirection(char *cmd)
{
    int i,k;
    char ** argv=argumentize(cmd);
    int argc=argCount(argv);
    for(i=0;i<argc;i++)
    {
        if(!strcmp(argv[i],"<"))
            break;
    }
    k=i+1;
    if(argc==k-1)
    {
        return NULL;
    }
    truncateCommand(cmd,k-1);

    return argv[k];
}

char* checkOutputRedirection(char *cmd)
{
    int i,k;
    char ** argv=argumentize(cmd);
    int argc=argCount(argv);

    for(i=0;i<argc;i++)
    {
        if(!strcmp(argv[i],">"))
            break;
    }
    k=i+1;
    if(argc==k-1)
    {
        return NULL;
    }
    truncateCommand(cmd,k-1);

    return argv[k];
}
char* checkAppendRedirection(char *cmd)
{
    int i,k;
    char ** argv=argumentize(cmd);
    int argc=argCount(argv);
    for(i=0;i<argc;i++)
    {
        if(!strcmp(argv[i],">>"))
            break;
    }
    k=i+1;
    if(argc==k-1)
    {
            return NULL;
    }    
    truncateCommand(cmd,k-1);
    
    return argv[k];
}
