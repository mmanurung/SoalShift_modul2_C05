#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>

int main() {
	char file_sumber[100];
	char x[100], y[100];
	char tambahan[100] = "_grey.png";
	char *ptr;
	char dir_sumber[100];
	char dir_tujuan[100];

	//daemon
	pid_t pid, sid; pid = fork();
	if (pid < 0) { exit(EXIT_FAILURE); }
	if (pid > 0) { exit(EXIT_SUCCESS); }
	umask(0); sid = setsid();
	if (sid < 0) { exit(EXIT_FAILURE); }
	if ((chdir("/")) < 0) { exit(EXIT_FAILURE); }
	close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);

	while(1){
		struct dirent *de;  // Pointer for directory entry
		DIR *dr = opendir("/home/nanda/nama"); // opendir() returns a pointer of DIR type.

		if (dr != NULL) {
			//printf("output:\n");
			while ((de = readdir(dr)) != NULL){ // if we were able to read somehting from the directory
				//char *strcpy(char *dest, const char *src)
				strcpy(dir_sumber, "/home/nanda/nama/");
				strcpy(dir_tujuan, "/home/nanda/modul2/gambar/");
				if (DT_DIR != de->d_type){
					strcpy(file_sumber, de->d_name);
 	                                ptr = strrchr(file_sumber, '.');
	                                strcpy(x, file_sumber);
                                        if (ptr && (strcmp(ptr, ".png") == 0)){
                                        	*ptr = 0;
                                        	strcpy(y, file_sumber);
	                                        strcat(y, tambahan);
        	                                strcat(dir_sumber, x);
                	                        strcat(dir_tujuan, y);

                        	                rename(dir_sumber, dir_tujuan);
                                	}
				}
			}
        		closedir(dr); // finally close the directory
		}
		sleep(5);
	}
	exit(EXIT_SUCCESS);
	return 0;
}
