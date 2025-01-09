#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

void	signal_manager(pid_t process)
{
	if (fork() == 0)
	{
		sleep(1);
		kill(process, SIGSTOP);
		sleep(5);
		kill(process, SIGCONT);
		sleep(1);

		exit(0);
	}
}

int main()
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		int i = 0;
		while (i < 10)
		{
			printf("[%d] counter: %i\n", getpid(), i);
			sleep(1);
			i++;
		}
		exit(0);
	}

	pid_t	test;
	int		wstatus;

	signal_manager(pid);
	while ((test = waitpid(pid, &wstatus, WNOHANG | WUNTRACED | WCONTINUED)) != -1) // WNOHANG   WUNTRACED
	{
		if (WIFEXITED(wstatus))
			printf("%d: Exited %d\n", test, WEXITSTATUS(wstatus)); 
		else if (WIFCONTINUED(wstatus))
			printf("%d: Continued\n",  test); 
		else if (WIFSTOPPED(wstatus))
			printf("%d: Stopped %d\n", test, WSTOPSIG(wstatus)); 
		else if (WIFSIGNALED(wstatus))
			printf("%d: Signaled by %d\n", test , WTERMSIG(wstatus)); 
		else
			printf("%d: WOW\n", test);
		sleep(1);
	}
}