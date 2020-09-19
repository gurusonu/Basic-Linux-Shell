#include "file.h"
#define rep1(i,a,b) for(i=a;i<b;i++)

int main(int argc,char * argv[])
{
    while(1)
    {
        CURR_FOREGROUND=-1;
        CURR_FOREGROUND_NAME=NULL;
        char ** cmd;
        struct utsname userInfo;
        uname(&userInfo);
        checkBackgroud();
        printf("<%s@%s:",getenv("USER"),userInfo.sysname);
        printf("%s>",dirName());
        
    	CURR_FOREGROUND_NAME = NULL;
    	CURR_FOREGROUND = -1;

        signal(SIGINT,CtrlCHandler);
    	signal(SIGTSTP,CtrlZHandler);
        cmd=input();

        int i;
        for(i=0;cmd[i]!=NULL;++i)
            {
                cmd[i]=parseCommand(cmd[i]);
                //execCmd(cmd[i]);
		pipeExec(cmd[i]);
            }
    }

    return 0;
}
