#include "minishell.h"

static size_t	operation_len(const char *s)
{
	if (ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0 \
		|| ft_strncmp(s, ">>", 2) == 0 || ft_strncmp(s, "<<", 2) == 0)
		return (2);
	else if (*s == '|' || *s == '<' || *s == '>')
		return (1);
	return (0);
}

static char	*get_line(int fd)
{
	size_t	nbytes;
	char 	*line;
	ssize_t	lines_read;

	nbytes = 0;
	if (ioctl(fd, FIONREAD, &nbytes) == -1)
		return (PRINT_SYSCALL_ERROR, NULL);
	line = malloc(sizeof(char) * (nbytes + 1));
	if (line == NULL)
		return (PRINT_ALLOCATE_ERROR, NULL);
	lines_read = read(fd, line, nbytes);
	if(lines_read == -1)
	{
		free(line);
		return (PRINT_SYSCALL_ERROR, NULL);
	}
	line[lines_read] = 0;
	return (line);
}

char	*expand_line(const char *s)
{
	int		pipe_fds[2];
	size_t	op_len;
	char *line;

	if (pipe(pipe_fds) == -1)
		return (PRINT_SYSCALL_ERROR, NULL);
	while (*s)
	{
		op_len = operation_len(s);
		if (op_len)
		{
			write(pipe_fds[1], " ", 1);
			write(pipe_fds[1], s, op_len);
			write(pipe_fds[1], " ", 1);
			s += op_len;
			continue ;
		}
		else
			write(pipe_fds[1], s, 1);
		s++;
	}
	close(pipe_fds[1]);
	line = get_line(pipe_fds[0]);
	close(pipe_fds[0]);
	return (line);
}