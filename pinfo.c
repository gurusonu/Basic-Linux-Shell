#include "file.h"
#define rep1(i,a,b) for(i=a;i<b;i++)
const int max_size3=1024;

int exec_pinfo(int pid)
{
	char *filePath = (char *)malloc(max_size3);
	char str_pid[10] = {"self"};
	char fileComm[128];
	int filePid;
	char fileState;
	long unsigned int vmsize;
	char exePath[1024];

	if(pid>0)
		sprintf(str_pid,"%d",pid);
    strcpy(filePath,"/proc/");
	strcat(filePath,str_pid);
	char *fileExePath=(char *)malloc(max_size3);
	strcpy(fileExePath,filePath);
    strcat(filePath,"/stat");
	FILE* fin = fopen(filePath,"r");
    strcat(fileExePath,"/exe");
	if(!fin)
	{
		printf("LoL:Check the pid\n");
		perror("LoL");
		return -1;
	}
	
	fscanf(fin,"%d %s %c",&filePid,fileComm,&fileState);
	strcat(filePath,"m");
	fclose(fin);
	FILE *finMem=fopen(filePath,"r");
	if(!finMem)
	{
		printf("LoL:Check the pid\n");
		perror("LoL");
		return -1;
	}
	fscanf(finMem,"%lu",&vmsize);
	printf("pid -- %d\n",filePid);
	printf("Process Status -- %c memory \n",fileState);
	printf("- %lu {Virtual memory}\n",vmsize);

	int check = readlink(fileExePath,exePath,max_size3);
	if(check<0)
	{
		printf("LoL:Error in determining path\n");
		perror("LoL");
		return -1;
	}
	exePath[check]='\0';
	printf("- Executable Path -- %s\n",exePath);
	fclose(finMem);
	free(filePath);
	return 0;
}
