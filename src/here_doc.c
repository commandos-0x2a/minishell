/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/21 15:09:11 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

int	heredoc_start_read(char *limiter, int out_fd)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
				ft_fprintf(2, "\n" PREFIX ": warning: " \
						"here-document delimited by " \
						"end-of-file (wanted `%s`)\n", limiter);
			break ;
		}
		if (ft_strncmp(line, limiter, limiter_len) == 0 && \
			(line[limiter_len] == '\n' || line[limiter_len] == '\0'))
		{
			free(line);
			break ;
		}
		write(out_fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}


int	heredoc_forever(char **tokens)
{
	int	fd;
	int	pipefd[2];

	fd = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0)
		{
			tokens++;
			if (fd > 0)
				close(fd);
			if (pipe(pipefd) == -1)
				return (-1);
			heredoc_start_read(*tokens, pipefd[1]);
			close(pipefd[1]);
			fd = pipefd[0];
		}
		tokens++;
	}
	return (fd);
}