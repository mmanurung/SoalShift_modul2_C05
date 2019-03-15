#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>

int main() {
	char *kill_argv[]={"pkill", "soal5", NULL};
	execv("/usr/bin/pkill",kill_argv);
}
