#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void	evaluation(char result[4096], int child_pid, char *prog_name, int argc)
{
	char	correct[4096];
	int		index;

	index = 0;
	index += sprintf(correct, "fd: 3\n");
	index += sprintf(correct + index, "ppid: %d\n", child_pid);
	index += sprintf(correct + index, "argv[0]: %s\n", prog_name);
	for (int i = 1; i < argc; i++)
		index += sprintf(correct + index, "argv[%d]: arg%d\n", i, i);
	if (strcmp(correct, result) == 0)
		printf("OK\n");
	else
		printf("KO\n");
}

int main()
{
	char	result[4096];
	int		out_fd;
	ssize_t	_read;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execl("./main.elf", "./main.elf", NULL);
		perror("./main.elf");
		exit(1);
	}

	wait(NULL);
	
	out_fd = open("out", O_RDONLY);
	if (out_fd == -1)
	{
		perror("out");
		return (1);
	}
	_read = read(out_fd, result, sizeof(result) - 1);
	close(out_fd);
	if (_read < 0)
	{
		perror("read");
		return (1);
	}
	result[_read] = '\0';
	evaluation(result, pid, "./victim.elf", 4);
	unlink("out");
	return (0);
}
