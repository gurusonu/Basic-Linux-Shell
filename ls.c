#include "file.h"
#define rep1(i,a,b) for(i=a;i<b;i++)


int cmd_pk_ls(char *path)
{
    DIR *dir;
    dir=opendir(path);
    int i;
    if(dir==NULL)
    {
         perror("LoL");
         return -1;
    }
    struct dirent *dir_ptr;
    dir_ptr=readdir(dir);
    while(dir_ptr)
    {
        if(dir_ptr->d_name[0]!='.')
            printf("%s\n",dir_ptr->d_name);
        dir_ptr=readdir(dir);
    }
    closedir(dir);
    return 0;
}
char * formatDate(char *str,time_t val)
{
    strftime(str,36,"%d.%m.%Y %H:%M:%S",localtime(&val));
    return str;
}
int print_pk_ls_l(char *path,char *fileName)
{
    char filePath[4096];
    struct stat file_buff;
    strcpy(filePath,path);
    strcat(filePath,"/");
    strcat(filePath,fileName);
    char permission[16];
    permission[10]='\0';
    int check = stat(filePath,&file_buff);
    if(check<0)
    {
        perror("LoL");
        return -1;
    }

    if(S_ISDIR(file_buff.st_mode))
        permission[0]='d';
    else
        permission[0]='-';
    
    if(file_buff.st_mode & S_IRUSR)
        permission[1]='r';
    else
        permission[1]='-';
    if(file_buff.st_mode & S_IWUSR)
        permission[2]='w';
    else
        permission[2]='-';
    if(file_buff.st_mode & S_IXUSR)
       permission[3]='x';
    else
        permission[3]='-';

    if(file_buff.st_mode & S_IRGRP)
      permission[4]='r';
    else
        permission[4]='-';
    if(file_buff.st_mode & S_IWGRP)
      permission[5]='w';
    else
        permission[5]='-';
    if(file_buff.st_mode & S_IXGRP)
      permission[6]='x';
    else
        permission[6]='-';

    if(file_buff.st_mode & S_IROTH)
        permission[7]='r';
    else
        permission[7]='-';
    if(file_buff.st_mode & S_IWOTH)
        permission[8]='w';
    else
        permission[8]='-';
    if(file_buff.st_mode & S_IXOTH)
        permission[9]='x';
    else
        permission[9]='-';

    char date[1024];
    printf("%s\t %d\t ",permission,file_buff.st_nlink);
    printf("%s\t %s\t ",getpwuid(file_buff.st_uid)->pw_name,getgrgid(file_buff.st_gid)->gr_name);
    formatDate(date,file_buff.st_mtime);
    printf("%lld\t ",file_buff.st_size);
    printf(" %s\t %s\n",date,fileName);
    
    return 0;
}
int cmd_pk_ls_a(char *path)
{
    DIR *dir;
    dir=opendir(path);
    int i;
    struct dirent *dir_ptr;
    dir_ptr=readdir(dir);
    if(dir==NULL)
    {
        perror("LoL");
        return -1;
    }

    while(dir_ptr)
    {
        printf("%s\n",dir_ptr->d_name);
        dir_ptr = readdir(dir);
    }
    closedir(dir);
    return 0;
}

int cmd_pk_ls_l(char *path)
{
    DIR *dir;
    dir = opendir(path);
    struct dirent *dir_ptr;
    dir_ptr = readdir(dir);
    if(dir==NULL)
    {
        perror("LoL");
        return -1;
    }

    while(dir_ptr)
    {
        if(dir_ptr->d_name[0]!='.')
        {
            print_pk_ls_l(path,dir_ptr->d_name);
            dir_ptr = readdir(dir);
            continue;
        }
        dir_ptr = readdir(dir);
    }

    closedir(dir);
    return 0;
}
int cmd_pk_ls_l_a(char *path)
{
    DIR *dir;
    dir = opendir(path);
    struct dirent *dir_ptr;
    dir_ptr = readdir(dir);
    if(dir==NULL)
    {
        perror("LoL");
        return -1;
    }
    
    while(dir_ptr!=NULL)
    {
        print_pk_ls_l(path,dir_ptr->d_name);
        dir_ptr = readdir(dir);
    }
    closedir(dir);
    return 0;
}
