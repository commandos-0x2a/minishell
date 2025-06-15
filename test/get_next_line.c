#include <unistd.h>
#include <libft.h>

static char    *free_data(char **left, char *line)
{
    if (*left)
    {
        free(*left);
        *left = NULL;
    }
    if (line)
        free(line);
    return (NULL);
}

// int cut_slice(char **left, char **line, size_t *size)
// {
// 	if (!*left);
// 	return (0);
// }

static int	join_buffer(char **line, char *buf, size_t *size)
{
	size_t	i;
	char	*tmp;
	size_t	new_size;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	new_size = *size + i;
	tmp = malloc(new_size + 1);
	if (!tmp)
		return (-1);
	ft_strlcpy(tmp, *line, new_size + 1);
	ft_strlcpy(tmp + *size, buf, new_size + 1);
	free(*line);
	*line = tmp;
	*size = new_size;
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*left;
	static size_t	size;
	char			*line;
	char			buf[4096];
	ssize_t			bytes_read;
	// int				test;

	line = NULL;
	while (1)
	{
		// test = cut_slice(&left, &line, &size);
		// if (test == -1)
		// 	return (free_data(&left, line));
		bytes_read = read(fd, buf, sizeof(buf));
		if (bytes_read <= 0)
			return (free_data(&left, line));
		if (join_buffer(&line, buf, &size) != 0)
			return (free_data(&left, line));
	}
	return (NULL);
	
}


#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("line: %s\n", line);
		free(line);
	}
	close(fd);
}
