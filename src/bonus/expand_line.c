/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:13:24 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/28 21:38:37 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	operation_len(const char *s)
{
	if (ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0
		|| ft_strncmp(s, ">>", 2) == 0 || ft_strncmp(s, "<<", 2) == 0)
		return (2);
	else if (*s == '|' || *s == '<' || *s == '>')
		return (1);
	return (0);
}

static char	*get_line(int fd)
{
	size_t	nbytes;
	char	*line;
	ssize_t	lines_read;

	nbytes = 0;
	if (ioctl(fd, FIONREAD, &nbytes) == -1)
	{
		print_error(__FILE__, __LINE__);
		return (NULL);
	}
	line = malloc(sizeof(char) * (nbytes + 1));
	if (line == NULL)
	{
		print_error(__FILE__, __LINE__);
		return (NULL);
	}
	lines_read = read(fd, line, nbytes);
	if (lines_read == -1)
	{
		free(line);
		print_error(__FILE__, __LINE__);
		return (NULL);
	}
	line[lines_read] = 0;
	return (line);
}

char	*expand_line(const char *s)
{
	int		pipe_fds[2];
	size_t	op_len;
	char	*line;

	if (pipe(pipe_fds) == -1)
	{
		print_error(__FILE__, __LINE__);
		return (NULL);
	}
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


static char	*allocate_expanded_line(const char *s)
{
	size_t	len;
	size_t	op_len;

	len = 0;
	while (*s)
	{
		op_len = operation_len(s);
		if (op_len)
			len += 2;
		len += op_len;
		s += op_len;
		len++;
		s++;
	}
	return (malloc(len));
}

char	*expand_line2(const char *s)
{
	char	*line;
	char	*s2;
	size_t	op_len;

	line = allocate_expanded_line(s);
	if (!line)
		return (NULL);
	s2 = line;
	while (*s)
	{
		op_len = operation_len(s);
		if (op_len)
		{
			*s2++ = ' ';
			while (op_len--)
				*s2++ = *s++;
			*s2++ = ' ';
		}
		*s2++ = *s++;
	}
	*s2 = '\0';
	return (line);
}
