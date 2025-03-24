#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void	print_result(char *result, int child_pid)
{
	char	correct[1024];

	sprintf(correct, "pid: %d\n", child_pid);
	if (strcmp(correct, result) == 0)
		printf("OK\n");
	else
		printf("KO\n");
}

int main()
{
	int		pipe_fd[2];
	char	buf[1024];
	ssize_t	_read;
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(pipe_fd[1]);
			exit(1);
		}
		close(pipe_fd[1]);
		execl("./main.elf", "./main.elf", NULL);
		perror("execl");
		exit(1);
	}
	close(pipe_fd[1]);

	wait(NULL);
	
	_read = read(pipe_fd[0], buf, sizeof(buf) - 1);
	close(pipe_fd[0]);
	if (_read < 0)
		return (1);
	buf[_read] = '\0';
	print_result(buf, pid);
	return (0);
}