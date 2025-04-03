#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


void	child(char id)
{
	char	buf[1024];
	ssize_t	_read;

	buf[0] = '\0';
	if (id % 3 == 0)
	{
		write(1, &id, 1);
		write(1, "> ", 2);
		_read = read(0, buf, sizeof(buf) - 1);
		buf[_read] = '\0';
	}
	kill(getpid(), SIGSTOP);

	printf("[child %d]: readed \"%s\"\n", getpid(), buf);
	exit(0);
}

int main()
{
	pid_t	pid[5];


	for (int i = 0; i < sizeof(pid) / sizeof(pid[0]); i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child('A' + i);
		if (waitpid(pid[i], NULL, WUNTRACED) == -1)
			return (1);
		printf("[parent] create process %d with pid %d\n", i, pid[i]);
		fflush(stdout);
	}
	for (int i = 0; i < sizeof(pid) / sizeof(pid[0]); i++)
	{
		kill(pid[i], SIGCONT);
		usleep(1000);
	}
	return (0);
}