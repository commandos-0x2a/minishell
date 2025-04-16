#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
	int		ret;
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		if (fork() == 0)
		{
			sleep(200);
			exit(0);
		}
		if (fork() == 0)
		{
			sleep(200);
			exit(0);
		}
		if (fork() == 0)
		{
			sleep(200);
			exit(0);
		}
		if (fork() == 0)
		{
			sleep(200);
			exit(0);
		}
		exit(0);
	}
	
	ret = waitpid(-getgid(), NULL, 0);
	printf("ret: %d\n", ret);
	ret = waitpid(-getgid(), NULL, 0);
	printf("ret: %d\n", ret);
	return (0);
}