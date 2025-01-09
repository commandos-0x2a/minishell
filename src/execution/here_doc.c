/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/09 19:09:17 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc_handler(char *limiter, int out_fd)
{
	char	buffer[4096];
	ssize_t	_read;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		if (isatty(0))
			write(1, "> ", 2);
		_read = read(0, buffer, sizeof(buffer));
		if (_read == -1)
			return (-1);
		if (_read == 0)
		{
			if (isatty(0))
				ft_fprintf(2, "\n"NAME": warning: here-document " \
							"delimited by end-of-file (wanted `%s`)\n", limiter);
			break ;
		}
		if (ft_strncmp(buffer, limiter, limiter_len - 1) == 0 \
						&& buffer[limiter_len] == '\n')
			break ;
		write(out_fd, buffer, _read);
	}
	return (0);
}

int	here_doc(char *limiter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	if (here_doc_handler(limiter, pipe_fd[1]) == -1)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
