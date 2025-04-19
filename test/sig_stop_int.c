#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t	g_sigint;

void	signal_handler(int signo)
{
	g_sigint = signo;
}

int main()
{
	pid_t	pid;
	
	g_sigint = 0;
	signal(SIGINT, signal_handler);
	if ((pid = fork()) == 0)
	{
		kill(getpid(), SIGSTOP);
		fprintf(stderr, "g_sigint: %d\n", g_sigint);
		return (0);
	}
	else if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	kill(pid, SIGINT);
	usleep(100);
	kill(pid, SIGCONT);
	wait(NULL);
	return (0);
}
