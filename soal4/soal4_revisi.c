#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

int main(){
	pid_t pid,sid;
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
		time_t waktu; double detik_ms;
		time(&waktu);
		struct stat st={0};
	        if(stat("/home/bella/Documents/makanan/makan_enak.txt",&st) == -1){
                	exit(1);
      		 }

       		detik_ms = difftime(waktu,st.st_atime);
      		int number=1;

      		char filename[100001], sequence[100001];
      		snprintf(sequence,sizeof(sequence),"%d",number);
       		struct stat file_parent = {0};

       		strcpy(filename,"home/bella/Documents/makanan/makan_sehat");
     		while(detik_ms<=30.0){
                 	snprintf(sequence,sizeof(sequence),"%d",number);
                 	strcat(sequence,".txt");
                 	strcat(filename,sequence);
                 	if(stat(filename,&file_parent) == -1){
                         	freopen(filename,"w+",stdout);
                         	fclose(stdout);
                         	break;
                  	}
                 	strcpy(filename,"/home/bella/Documents/makanan/makan_sehat");
                 	number++;
        	}
		sleep(5);
	}
	exit(EXIT_SUCCESS);
}
