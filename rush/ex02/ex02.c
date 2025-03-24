#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
	send output to file called 'out'

	make redirection output and send args
	make redirection input
*/

int	copy_content(int in_fd, int out_fd)
{
	char	buf[1024];
	ssize_t	_read;

	while (1)
	{
		_read = read(in_fd, buf, sizeof(buf));
		if (_read == 0)
			break;
		if (_read == -1)
		{
			perror("read");
			return (-1);
		}
		if (write(out_fd, buf, _read) != _read)
		{
			perror("write");
			return (-1);
		}
	}
	return (0);
}

int main(int argc, char **argv)
{
	int	in_fd;
	int	out_fd;
	
	if (argc != 3)
	{
		write(2, "Usage: ./ex01_test in_fd out_fd\n", 11);
		return (1);
	}
	in_fd = atoi(argv[1]);
	out_fd = atoi(argv[2]);
	if (in_fd < 3 || out_fd < 3)
	{
		write(2, "input fd or output fd is std\n", 29);
		return (1);
	}
	if (copy_content(in_fd, out_fd) < 0)
		return (1);
	return (0);
}
