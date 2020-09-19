#include "file.h"
#define rep1(i,a,b) for(i=a;i<b;i++)

struct Process
{
  int  pid;
  char cmd[1024];
  int status;
};
const char *SUPPORTED_CMD[]={
    "pwd","cd","echo","exit","ls","pinfo","clock","remindme","setenv","unsetenv",
    "jobs","kjob","fg","bg","overkill","quit","mkdir","mgdir"};


struct Process backgroundProcess[1024];
int processPointer=0;
const int max_size1=1000;


int findCmdNo(char *cmd)
{
    int i,n,count=0;
    n=strlen(cmd);
    
    rep1(i,0,n)
        if(cmd[i]==' ')
            break;
    count=i;
    char *command = (char *)malloc(sizeof(char)*count+2);
    rep1(i,0,count)
        command[i]=cmd[i];
    command[i]='\0';
    int totalCommand=sizeof(SUPPORTED_CMD)/sizeof(char*);
    rep1(i,0,totalCommand)
        if(strcmp(command,SUPPORTED_CMD[i])==0)
        {
   			free(command);
            return i;
        }

     free(command);
     return -1;
}
int exec_pk_ls(char *cmd)
{
    int aflag=0,lflag=0;
    char **argv = argumentize(cmd);
    int argc = argCount(argv);

    int numberOfParameter = 1;
    if(argc==1)
    {
    		return cmd_pk_ls(".");
    }     
    else if(argc==2 && argv[1][0]!='-')
        return cmd_pk_ls(argv[1]);
    if(argv[1][0]=='-' && argc>=2)
    {
        if(strcmp("-a",argv[1])==0)
            aflag=1;
        else if(strcmp("-l",argv[1])==0)
            lflag=1;
        else if(strcmp("-la",argv[1])==0||(strcmp("-al",argv[1])==0))
        {
            aflag=1;
            lflag=1;
        }
        else
         {
             fprintf(stderr,"%s\n","LoL:Wrong flag used with ls");
             return -1;
         }
         numberOfParameter++;
    }
    if(argc>=3 && argv[2][0]=='-')
    {
        numberOfParameter++;
        if((strcmp("-a",argv[2]))==0)
            aflag=1;
        else if((strcmp("-l",argv[2]))==0)
            lflag=1;
        else if(strcmp("-la",argv[2])==0||(strcmp("-al",argv[2])==0))
        {
            aflag=1;
            lflag=1;
        }
        else
        {
            fprintf(stderr,"%s\n","LoL:Wrong flag used with ls");
            return -1;
        }
    }
    if(numberOfParameter==argc)
    {
        if(aflag!=0 && lflag!=0)
            return cmd_pk_ls_l_a(".");
        else if(aflag!=0)
            return cmd_pk_ls_a(".");
        else if(lflag!=0)
            return cmd_pk_ls_l(".");
        else
            return cmd_pk_ls(".");
    }
    int i;
    for(i=numberOfParameter;i<argc;i++)
    {
        if(aflag!=0 && lflag!=0)
            return cmd_pk_ls_l_a(argv[i]);
        else if(aflag!=0)
            return cmd_pk_ls_a(argv[i]);
        else if(lflag!=0)
            return cmd_pk_ls_l(argv[i]);
        else
            return cmd_pk_ls(argv[i]);
    }
    return 0;
}

int exec_pk_pwd()
{
    char *path=(char *)malloc(max_size1);
    getcwd(path,max_size1);

    printf("%s\n",path);
    free(path);
    return 0;
}
int exec_pk_cd(char *cmd)
{
	int temp;
    char **argv=argumentize(cmd);
    int argc = argCount(argv);
    if(argc!=2)
    {
    	if(argc!=1)
        {
        	fprintf(stderr,"%s\n","LoL:Enter as cd <path> or just cd");
        	return -1;
        }
    }
    if(argc==1 || strcmp("~",argv[1])==0)
    {
        int check=chdir(getenv("PWD"));
        if(check<0)
            perror("LoL");
    }
    else
    {
        int check = chdir(argv[1]);
        if(check<0 || argc==1)
            perror("LoL");
    }
    return 0;
}


int exec_pk_pinfo(char *cmd)
{
	int i;
    char **argv=argumentize(cmd);
    int argc=argCount(argv);
    if(argc==1)
        return exec_pinfo(0);
    else
    {
        rep1(i,1,argc)
            exec_pinfo(atoi(argv[i]));
    }
    return 0;
}

int exec_pk_setenv(char *cmd)
{
	int i,check=0;
    char **argv = argumentize(cmd);
    int argc = argCount(argv);

    if(argc==3)
    {
		check=setenv(argv[1],argv[2],1);
    }
    else if(argc!=2 && argc!=3)
    {
        fprintf(stderr,"%s\n","LoL:Enter as setenv <variable> or setenv <variable> <value>");
        return -1;
    }
    else
    {
        check=setenv(argv[1],"",1);
    }
    if(check<0)
    {
        perror("LoL::Setenv:");
        return -1;
    }
    return 0;
}
int exec_pk_unsetenv(char *cmd)
{
	int i,check=0;
    char **argv = argumentize(cmd);
    int argc=argCount(argv);
    if(argc!=2)
    {
        fprintf(stderr,"%s\n","LoL:Enter as unsetenv <variable>");
        return -1;
    }
    else
    {
	    check=unsetenv(argv[1]);
	    if(check<0 && argc==2)
	    {
	        perror("LoL::Setenv:");
	        return -1;
	    }
    }
    return 0;
}
int exec_pk_fg(char *cmd)
{
	int i;
    char **argv=argumentize(cmd);
    int argc=argCount(argv);
    int pindex=atoi(argv[1]);
 
    if(argc!=2)
    {
        fprintf(stderr,"%s\n","LoL:Enter as fg <process index from jobs>");
        return -1;
    }

    int count=0,status1,check;
    rep1(i,0,processPointer)
    {
        if(backgroundProcess[i].pid)
            ++count;
        if(count==pindex)
        {
        	int status;
            pid_t wpid=waitpid(backgroundProcess[i].pid,&status,WUNTRACED|WCONTINUED);
            check=kill(backgroundProcess[i].pid,SIGCONT);
            //Remove from background process array
            if(check==0)
                backgroundProcess[i].pid=0;
            return check;
        }
    }
    if(i==processPointer || count)
    {
        fprintf(stderr,"%s\n","LoL:Not valid process index use jobs for index\n");
        return -1;
    }
    return 0;
}
int exec_pk_echo(char *cmd)
{
	int i,temp;
    char **argv=argumentize(cmd);
    int argc=argCount(argv);

    rep1(i,1,argc)
        printf("%s ",argv[i]);
    printf("\n");
    return 0;
}
int exec_pk_bg(char *cmd)
{
	int i,count=0;
    char **argv=argumentize(cmd);
    int argc=argCount(argv);
    int pindex=atoi(argv[1]);
    if(argc!=2)
    {
        fprintf(stderr,"%s\n","LoL:Enter as bg <process index from jobs>");
        return -1;
    }
    int temp;
    rep1(i,0,processPointer)
    {
        if(backgroundProcess[i].pid)
            ++count;
        if(count==pindex)
        {
            int check=kill(backgroundProcess[i].pid,SIGCONT);
            temp=i;
            backgroundProcess[i].status = 1;
            return check;
        }
    }
    if(processPointer==i || count)
    {
        fprintf(stderr,"%s\n","LoL:Not valid process index use jobs for index\n");
        return -1;
    }
    return 0;
}
int exec_pk_overkill()
{
	char c;
	int count=0;
    printf("Overkill will kill all background processes. Are you sure you want to continue(y/n)?");
    scanf("%c",&c);
    if(c!='y' && c!='Y')
        return -1;
    int i;
    rep1(i,0,processPointer)
        if(backgroundProcess[i].pid)
            kill(backgroundProcess[i].pid,9);
    return 1;
}
int exec_pk_jobs(char *cmd)
{
	int check=0;
    char **argv=argumentize(cmd);
    int argc=argCount(argv);

    if(argc!=1)
    {
        fprintf(stderr,"%s\n","LoL:Enter as jobs\n");
        return -1;
    }
    else
    {
	    int count=0,i;
	    rep1(i,0,processPointer)
	    {
	        if(backgroundProcess[i].pid)
	        {
	            ++count;
	            if(backgroundProcess[i].status)
	            {
	                printf("\t[%d]\trunning\t%s\t[%d]\n",count,backgroundProcess[i].cmd,backgroundProcess[i].pid);
	            }
	            else
	            {
	                printf("\t[%d]\tstopped\t%s\t[%d]\n",count,backgroundProcess[i].cmd,backgroundProcess[i].pid);
	            }
	        }
	    }
	}
    return 0;
}
int exec_pk_kjob(char *cmd)
{
	int check=0;
    char **argv=argumentize(cmd);
    int argc=argCount(argv);
    
    if(argc!=3)
    {
        fprintf(stderr,"%s\n","LoL:Enter as kjob <process index> <signal number>\n");
        return -1;
    }
    else
    {
	    int count=0;
	    int pid=atoi(argv[1]);
	    int sig=atoi(argv[2]);
	    int i;
	    rep1(i,0,processPointer)
	    {
	        if(backgroundProcess[i].pid)
	            count++;
	        if(pid==count && argc==3)
	        {
	            int check;
	            check=kill(backgroundProcess[i].pid,sig);
	            return check;
	        }
	    }
	    if(processPointer==i && argc==3)
	    {
	        fprintf(stderr,"%s\n","Not valid process index use jobs for index\n");
	        return -1;
	    }
	}
    return 0;
}

void CtrlCHandler(int sig_num)
{
    if(CURR_FOREGROUND==-1)
        return;
    else
    {	
    	kill(CURR_FOREGROUND,SIGINT);
		fflush(stdout);
	}
}
void CtrlZHandler(int sig_num)
{
    if(CURR_FOREGROUND==-1)
        return;
    else
    {
	    kill(CURR_FOREGROUND,SIGTSTP);
	    backgroundProcess[processPointer].status=0;
	    backgroundProcess[processPointer].pid=CURR_FOREGROUND;
	    strcpy(backgroundProcess[processPointer].cmd,CURR_FOREGROUND_NAME);
	    processPointer+=1;
	    printf("[+] %s [%d]\n",CURR_FOREGROUND_NAME,CURR_FOREGROUND);
		fflush(stdout);
	}
}
int launch_cmd(char *cmd)
{
	int background=0;
    int status=0;
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    pid_t pid,wpid;

    if(strcmp(argv[argc-1],"&")==0)
        background = 1;
    pid=fork();

    if(pid<0)
    {
        perror("LoL");
        _exit(1);
    }
    else if(!pid)
    {
        if(background!=0)
            argv[argc-1]=NULL;
        int check;
        check=execvp(argv[0],argv);
        if(check<0)
        {
            perror("LoL");
            _exit(1);
        }
    }
    else if(background==0)
    {
        //parent Process for forground Process
        CURR_FOREGROUND=pid;
        CURR_FOREGROUND_NAME=argv[0];
            wpid=waitpid(pid,&status,WUNTRACED);
            if(wpid<0)
            {
                perror("LoL");
            }
    }
    else
    {
        //parent process for background Process
        backgroundProcess[processPointer].pid=pid;
        backgroundProcess[processPointer].status=1;
        kill(pid,SIGCONT);
        strcpy(backgroundProcess[processPointer].cmd,argv[0]);
        processPointer+=1;
        printf("[+] %s [%d]\n",argv[0],pid);
    }
    return status;
}
int checkBackgroud()
{
    int i,wpid,wpid2,status;
    rep1(i,0,processPointer)
    {
        if(backgroundProcess[i].pid)
        {
            wpid=waitpid(backgroundProcess[i].pid,&status,WNOHANG);
            if(wpid==backgroundProcess[i].pid)
            {
            	wpid2=wpid;
                printf("LoL: %s with pid %d exited with status %d\n",backgroundProcess[i].cmd,wpid,WIFEXITED(status));
                backgroundProcess[i].pid=0;
            }
        }
    }
    return 0;
}
int execCmd(char *cmd)
{
    int original_stdout = dup(1);
    int original_stdin = dup(0);
    char *str;
    int fd;
    int commandNumber=findCmdNo(cmd);
    str=checkInputRedirection(cmd);
    if(str)
    {
        fd=open(str,O_RDONLY);

        if(fd==-1) 
        {
          perror("Failed to open file");
        }  
        close(0);

        if(dup2(fd,0)!=0)  
        {
          perror("dup2 fail");
        }
        close(fd);

    }
    str=checkOutputRedirection(cmd);
    if(str)
    {
        fd=open(str,O_WRONLY | O_CREAT | O_TRUNC,0644);

        if(fd==-1)
        {
            perror("Failed to open file");
        }       
        close(1);

        if(dup2(fd,1)!=1)  
        {
			perror("dup2 fail");
		}
        close(fd);
    }
    str=checkAppendRedirection(cmd);
    if(str)
    {
        fd=open(str, O_WRONLY | O_CREAT | O_APPEND,0644);

        if(fd == -1)
        {
            perror("Failed to open file");
        }
        close(1);

        if(dup2(fd,1)!=1) 
        { 
         	perror("dup2 fail");
        }
        close(fd);
    }
    int status;
    if(commandNumber==-1)
        status=launch_cmd(cmd);

    if(commandNumber==0)
    	status=exec_pk_pwd();
    else if(commandNumber==1)
    	status=exec_pk_cd(cmd);
    else if(commandNumber==2)
    	status=exec_pk_echo(cmd);
    else if(commandNumber==3)
    	_exit(0);
    else if(commandNumber==4)
    	status=exec_pk_ls(cmd);
    else if(commandNumber==5)
    	status=exec_pk_pinfo(cmd);
    else if(commandNumber==8)
    	status=exec_pk_setenv(cmd);
    else if(commandNumber==9)
    	status=exec_pk_unsetenv(cmd);
    else if(commandNumber==10)
    	status=exec_pk_jobs(cmd);
    else if(commandNumber==11)
    	status=exec_pk_kjob(cmd);
    else if(commandNumber==12)
    	status=exec_pk_fg(cmd);
    else if(commandNumber==13)
    	status=exec_pk_bg(cmd);
    else if(commandNumber==14)
    	status=exec_pk_overkill(cmd);
    else if(commandNumber==15)
    {
    	status=exec_pk_overkill(cmd);
    	_exit(0);
    }	

    
    dup2(original_stdout,1);
    dup2(original_stdin,0);
    close(original_stdout);
    close(original_stdin);
    checkBackgroud();
    return status;
}
