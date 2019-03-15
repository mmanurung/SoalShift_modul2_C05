#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

int main() {
	struct stat sb; //pointer to stat struct
	char elen[100] = "/home/nanda/hatiku/elen.ku";
	int perintah; //perintah utk menghapus
	//daemon
	pid_t pid, sid; pid = fork();
	if (pid < 0) { exit(EXIT_FAILURE); }
	if (pid > 0) { exit(EXIT_SUCCESS); }
	umask(0); sid = setsid();
	if (sid < 0) { exit(EXIT_FAILURE); }
	if ((chdir("/")) < 0) { exit(EXIT_FAILURE); }
	close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);

	while(1) {// main program here
		stat(elen, &sb); //stat system call

		struct passwd *pw = getpwuid(sb.st_uid);
		struct group  *gr = getgrgid(sb.st_gid);

		if(strcmp(pw->pw_name, "www-data")==0 && (gr->gr_name, "www-data")==0){
			//change permission https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtchm.htm
			//int chmod(const char *pathname, mode_t mode);
			chmod(elen, S_IRWXU | S_IRWXG); //read, write, execute/search by owner or group
			perintah = remove(elen);
		}

		sleep(3);
	}
	exit(EXIT_SUCCESS);
}

/*  https://stackoverflow.com/questions/36069748/c-get-owner-and-group-of-file-directory
    struct stat sb;
    char outstr[200];

    stat(file_or_dir_name, &sb);

    struct passwd *pw = getpwuid(sb.st_uid);
    struct group  *gr = getgrgid(sb.st_gid);

    printf("%s %s\n", pw->pw_name, gr->gr_name);
*/

