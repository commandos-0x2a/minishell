#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	fprintf(stderr, "%s PID:%d, PPID:%d, PGID:%d\n", argv[1], getpid(), getppid(), getpgid(getpid()));
	sleep(1);
	fprintf(stderr, "%s PID:%d, PPID:%d, PGID:%d\n", argv[1], getpid(), getppid(), getpgid(getpid()));

}