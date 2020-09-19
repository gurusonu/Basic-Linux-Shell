#include "file.h"
#define rep1(i,a,b) for(int i=a;i<b;i++)

char * parseCommand(char * cmd)
{
    int leng=strlen(cmd);
    int i,count=0;
    int j=0;
    rep1(i,0,leng)
        if(!(cmd[i]==' ' || cmd[i]=='\t'))
            break;

    leng-=count+i;   
    leng-=count;    
    for(i=0;i<=leng;i++)  
        cmd[i]=cmd[i+count];
    
    count=0;
    char *parsed=strdup(cmd);
 
    rep1(i,0,leng+1)
        if(cmd[i]==' '|| cmd[i]=='\t')
            count++;
        else
        {
            if(count!=0)
            {
                parsed[j++]=' ';
                count=0;
            }
            parsed[j++]=cmd[i];
        }
    return parsed;
}

