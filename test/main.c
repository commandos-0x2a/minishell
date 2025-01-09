#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int pipefd[2];

volatile int status;

void send_msg(int pid, void *msg)
{
	write(pipefd[1], &msg, 8);
	usleep(100);
	kill(pid, SIGUSR1);
	usleep(100);
}

void child_receive_msg(int sig)
{
	ssize_t	_read;
	char buf[8];
	_read = read(pipefd[0], buf, sizeof(buf));
	if (_read != sizeof(buf))
	{
		perror("child read pipe");
		exit(1);
	}

	if ((*((void **)buf)) == (void *)0)
	{
		status = 1;
		return ;
	}
	printf("receive (%d): %#lx", getpid(), *((unsigned long*)buf));
	printf("\n");
	send_msg(getppid(), (void *)0x12345678);
}

void parent_receive_msg(int sig)
{
	ssize_t	_read;
	char buf[8];
	_read = read(pipefd[0], buf, sizeof(buf));
	if (_read != sizeof(buf))
	{
		perror("child read pipe");
		exit(1);
	}
	printf("receive (%d): %#lx", getpid(), *((unsigned long*)buf));
	printf("\n");
}

int	main(void)
{
	void *ptr;


	ptr = malloc(128);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}

	int pid = fork();
	if (pid == 0)
	{
		signal(SIGUSR1, child_receive_msg);
		status = 0;
		while (!status)
			usleep(10000);
		exit(0);
	}
	signal(SIGUSR1, parent_receive_msg);
	sleep(1);
	send_msg(pid, ptr);
	send_msg(pid, NULL);
	wait(NULL);
	return (0);
}
