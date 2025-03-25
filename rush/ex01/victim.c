#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
	send output to file called 'out'

	check if run execve in child process
	make redirection output and send args
*/

int main(int argc, char **argv)
{
	int	fd;
	int	i;

	fd = open("/dev/null", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	printf("fd: %d\n", fd);
	close(fd);
	printf("ppid: %d\n", getppid());
	i = 0;
	while (i < argc)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
	return (0);
}
