#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
	pid_t	pid;

	sleep(2);
	kill(pid, SIGSTOP);
	printf("stop\n");
	sleep(2);
	kill(pid, SIGCONT);
	waitpid(pid, NULL, 0);

	return (0);
}