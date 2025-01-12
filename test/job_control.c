#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	printf("parent PID:%d, PPID:%d, PGID:%d\n", getpid(), getppid(), getpgid(getpid()));
	if (fork() == 0)
	{
		printf("child1 PID:%d, PPID:%d, PGID:%d\n", getpid(), getppid(), getpgid(getpid()));
		if (fork() == 0)
		{
			printf("child2 PID:%d, PPID:%d, PGID:%d\n", getpid(), getppid(), getpgid(getpid()));
			exit(0);
		}
		wait(NULL);
		exit(0);
	}
	wait(NULL);
}