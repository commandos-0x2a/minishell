#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int	pipeline_iter(int i)
{
	pid_t	pid;

	if (i == 0)
	{
		if ((pid = fork()) == 0)
		{

			return (0);
		}
		return (1); // goto parent
	}
	if (pipeline_iter(i - 1) != 0)
		return (1); // goto parent
	if (fork() == 0)
		exit(0);
	return (0);
}

int main()
{
	printf("main: pid: %d\n", getpid());
	if (pipeline_iter(10) == 0)
	{
		return (0);
	}
	return (0);
}