#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	struct rusage	rusage;
	pid_t			target;

	target = fork();
	if (target == 0)
	{
		sleep(1);
		char	*argv[] = {"ls", NULL};
		execve("/bin/ls", argv, NULL);
		return (0);
	}
	printf("target pid: %d\n", target);
	wait4(target, NULL, 0, &rusage);
	printf("system time used (PL): %d\n", rusage.ru_stime.tv_usec);
}