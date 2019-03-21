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
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
		struct stat sb; //pointer to stat struct
                char elen[100] = "/home/nanda/hatiku/elen.ku";
                int perintah; //perintah utk menghapus

                stat(elen, &sb); //stat system call

                struct passwd *pw = getpwuid(sb.st_uid);
                struct group  *gr = getgrgid(sb.st_gid);
                //int chmod(const char *pathname, mode_t mode);
                //chmod(elen, 0777); //read, write, execute/search by owner or group or other
                if((strcmp(pw->pw_name, "www-data")==0) && (strcmp(gr->gr_name, "www-data")==0)){
                        chmod(elen, 0777);
                        perintah = remove(elen);
                }

    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
