#include<stdio.h>
#include<fcntl.h>
#include<signal.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

static void sighandler(int signo) {
	int fd;
	switch(signo) {
		case SIGINT:
			/*
			apparently the first line after case label can't have
			declarations
			*/
			fd = open("exit_status.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
			
			if (fd == -1) {
				printf("errno: %d, %s\n", errno, strerror(errno));
				exit(2);
			}
			
			char s[64];
			sprintf(s, "Process %d exited from SIGINT\n", getpid());
			if (write(fd, s, strlen(s)) == -1) {
				printf("errno: %d, %s\n", errno, strerror(errno));
				exit(2);
			}
			
			close(fd);
			
			exit(1);
		break;
		
		case SIGUSR1:
			printf("parent PID: %d\n", getppid());
		break;
	}
}

int main() {
	umask(0000);
	
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	
	while (1) {
		printf("PID: %d\n", getpid());
		sleep(1);
	}
	
	return 0;
}
