#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<ctype.h>

int main(int argc,char* argv[],char* envp[])
{
    while(1)
    {
        printf("cgl @ localhost ~]$ ");
        fflush(stdout);

        char buff[128]={0};
        fgets(buff,128,stdin);
        buff[strlen(buff)-1] = 0;
        char *my_argv[40];
        my_argv[0] = buff;
        int  i = 1;
        char*p = buff;
         while(*p)
            {
              if(isspace(*p))
                {
                  *p = '\0';
                   p++;
                   my_argv[i] = p;
                   i++;
                }
               else
                {  
                   p++;
                }
            }
         my_argv[i] = NULL;


        if(strncmp(buff,"exit",4)==0)
        {
            break;
        }
        pid_t pid=fork();
        assert(pid!=-1);
        if(pid==0)
        {
             execvp(my_argv[0],my_argv);
             perror("execlp error");
             exit(0);

        }
         wait(NULL);
    }
}
