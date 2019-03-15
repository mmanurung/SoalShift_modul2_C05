#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(){
       int i=1;
       pid_t pid, sid;
       pid=fork();

       if(pid<0)
               exit(EXIT_FAILURE);
       if(pid>0)
               exit(EXIT_SUCCESS);

       umask(0);
       sid=setsid();

       if(sid<0)
               exit(EXIT_FAILURE);
       if((chdir("/"))<0)
               exit(EXIT_FAILURE);

       close(STDIN_FILENO);
       close(STDOUT_FILENO);
       close(STDERR_FILENO);

       while(1){
               int num=1; char buffer[50],foldername[101];
               time_t waktu = time(NULL);
               if(!((num-1)%30)){
                       memset(buffer,0,sizeof(buffer));
                       strftime(buffer,50,"%d:%m:%Y-%H-%M", localtime(&waktu));
                       sprintf(foldername,"/home/bella/log");
                       strcat(foldername,buffer);
                       mkdir(foldername,0777);
                       num=1;
               }
               strftime(buffer,50,"%d:%m:%Y-%H-%M",localtime(&waktu));
               char filename[101],filename_ext[101];
               sprintf(filename,"/home/bella/log/");
               strcat(filename,buffer);
               snprintf(filename_ext,sizeof(filename_ext),"log%d.log",num);
   	               strcat(filename,filename_ext);
               if(!fork()){
                       char *cp_argv[]={"cp","/var/log/syslog",filename,NULL};
                       execv("/bin/cp",cp_argv);
               }
               num++;
               sleep(60);
       }
       exit(EXIT_SUCCESS);
}
