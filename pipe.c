#include "file.h"
#define rep(i,a,b) for(int i=a;i<b;i++)

const int MAX_PIPE=16;
const int MAX_SIZE=16;

int checkPipe(char *cmd)
{
    int n=strlen(cmd);
    int i;
    for(i=0;i<n;i++)
        if(cmd[i]=='|')
        {
        	return i;
        }    
    return -1;
}

char ** parsePipe(char* cmd)
{
    int count=0;
	char *sep="|";
    char *str=strdup(cmd);
    char **pipelets=malloc(MAX_PIPE * sizeof(char *));

    pipelets[count++]=strtok(str,sep);
    while(pipelets[count-1])
    {
        pipelets[count++]=strtok(NULL,sep);
    }
    count++;
    pipelets[count-1]=NULL;

    return pipelets;
}	
int pipeExec(char *cmd)
{
    if(checkPipe(cmd)==-1)
        return execCmd(cmd);
    int i;
    char **pipelets = parsePipe(cmd);
    int pipe_num;
    pipe_num=argCount(pipelets);

    for(i=0;i<pipe_num;i++)
        pipelets[i]=parseCommand(pipelets[i]);

    int fildes[2];
    int original_stdout=dup(1);
    int original_stdin=dup(0);
    int j=i+1;
    int fd = dup(0);
    for(i=0;i<pipe_num;i++)
    {
        if(dup2(fd,0)==-1)
        {    
            perror("LoL::dup2 fail");
        }
        close(fd);
        if(pipe_num-1==i)
        {
            if(dup2(original_stdout,1)+1==0)
            { 
               perror("LoL::dup2 fail");
			}
            close(original_stdout);
        }
        else
        {
        	fd=fildes[0];
            pipe(fildes);
            if(dup2(fildes[1],1)+1==0)
            {    
                perror("LoL::dup2 fail");
            }
            close(fildes[1]);
        }
        int flag=execCmd(pipelets[i]);
        if(flag!=0)
            break;
    }

    dup2(original_stdout,1);
    dup2(original_stdin,0);
    close(original_stdout);
    close(original_stdin);
    if(pipe_num!=i)
    {
        printf("Command %d not executed properly\n",j);
        return -1;
    }
    return 0;
}
