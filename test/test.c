#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int		fd;
	char	*msg;
	size_t	len;
	int		exit_status;

	if (argc != 4)
	{
		fprintf(stderr, "Usage: %s fd msg exit_status\n", argv[0]);
		return (1);
	}
	fd = atoi(argv[1]);
	msg = argv[2];
	len = strlen(msg);
	exit_status = atoi(argv[3]);
	write(fd, msg, len);
	write(fd, "\n", 1);
	return (exit_status);
}