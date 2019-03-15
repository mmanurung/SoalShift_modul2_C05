#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main(){
    chdir("home/bella/modul2");
    int st_parent1, rw_pipe1[2], rw_pipe2[2];
    char tmp[100001];
    char *unzip_argv[]={"unzip","campur2.zip",NULL};
    char *ls_argv[]={"ls","campur2",NULL};
    char *grep_argv[]={"grep",".txt$",NULL};

    if(!fork()){
        struct stat st = {0};
        if(stat("campur2",&st)!=0)
		execv("/usr/bin/unzip",unzip_argv);
        exit(1);
    }
    else {
        while(!wait(&st_parent1));
        pipe(rw_pipe1); pipe(rw_pipe2);
        if(!fork()){
            close(rw_pipe2[0]); close(rw_pipe2[1]); close(rw_pipe1[0]);
            dup2(rw_pipe1[1],STDOUT_FILENO);
            close(rw_pipe1[1]);
            execv("/bin/ls",ls_argv);
         }
         else {
            wait(NULL);
            if(!fork()){
                close(rw_pipe2[0]);
                dup2(rw_pipe2[1],STDOUT_FILENO);
                close(rw_pipe2[1]); close(rw_pipe1[1]);
                dup2(rw_pipe1[0],STDIN_FILENO);
                close(rw_pipe1[0]);
                execv("/bin/grep",grep_argv);
            }
            else {
                close(rw_pipe2[1]); close(rw_pipe1[0]); close(rw_pipe1[1]);
                int byte = read(rw_pipe2[0],tmp,sizeof(tmp));
		freopen("daftar.txt","w+",stdout);
		printf("%s\n",tmp);
		fclose(stdout);
                close(rw_pipe2[0]);
            }
        }
    }
}
