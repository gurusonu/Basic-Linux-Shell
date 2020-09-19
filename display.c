#include "file.h"
#define rep1(i,a,b) for(int i=a;i<b;i++)
const int max_size=1000;

char * dirName()
{
    int length_home,length_path,i;
    char *path=(char *)malloc(max_size);
    char *home=getenv("PWD");

    getcwd(path,max_size);
 
    if(strlen(path)==strlen(home))
        return "~"; 
    else if(strlen(home)<=strlen(path))
    {
    	int i;
        char *rel_path=(char *)malloc(sizeof(path)+1);
        rel_path[0]='~';
        length_home=strlen(home);
        length_path=strlen(path);
        for(i=length_home;i<=length_path;i++)
            rel_path[i-length_home+1]=path[i];
        return rel_path;
    }

    return path;
}

