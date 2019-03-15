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
	if((chdir("/")) < 0)
		exit(EXIT_FAILURE);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(1){
		chdir("home/bella/Documents/makanan");
		struct stat status={0}, status_file={0};
		time_t waktu; time(&waktu); ctime(&waktu);
		int num=1;
		FILE *find_file;
		if(stat("makanan_enak.txt",&status)<0){
			printf("Failed\n");
			exit(1);
		}
		double diff = difftime(waktu,status.st_atime);
		char *filename="home/bella/Documents/makanan";
		strcat(filename,"makan_sehat");
		while(30.00 >= diff && diff>=0){
			sprintf(filename,"makan_sehat%d.txt",num);
			if(stat(filename,&status_file)<0){
				find_file=fopen(filename,"w+");
				fclose(find_file); break;
			}
			num++;
			strcpy(filename,"home/bella/Documents/makanan/makan_sehat");
		}
	}
}
