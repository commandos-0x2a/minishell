#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int		fd;
	int		i;
	char	*cmd;

	fd = open("/dev/ttys054", O_WRONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}

	cmd = "ls -la";
	i = 0;
	while (cmd[i])
	{
		write(fd, cmd + i, 1);
		usleep(500000);
		i++;
	}
	write(fd, "\n", 1);
	return (0);
}