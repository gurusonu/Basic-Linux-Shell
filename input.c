#include "file.h"
#define rep1(i,a,b) for(i=a;i<b;i++)
const int max_size2=1024;

char ** input()
{
    char buffer[max_size2];
    char *b=buffer;
    size_t bufsize=max_size2;

    int n=getline(&b,&bufsize,stdin);
    return tokanize(buffer);
}
