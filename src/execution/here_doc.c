/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/22 22:50:29 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

static int	here_doc_start_read(char *limiter, int out_fd)
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

int	*run_all_heredoc(char **tokens, int nb_pipeline)
{
	int	pipe_fd[2];
	int	i;
	int	*heredoc_fds;

	heredoc_fds = malloc(sizeof(int) * nb_pipeline);
	if (!heredoc_fds)
		return (NULL);
	ft_memset(heredoc_fds, -1, sizeof(int) * nb_pipeline);
	i = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "|") == 0)
			i++;
		if (ft_strcmp(*tokens, "<<") == 0)
		{
			if (heredoc_fds[i] > -1)
				close(heredoc_fds[i]);
			if (pipe(pipe_fd) == -1)
			{
				perror(PREFIX"pipe here doc");
				while (--i >= 0)
					if (heredoc_fds[i] > -1)
						close(heredoc_fds[i]);
				free(heredoc_fds);
				return (NULL);
			}
			here_doc_start_read(*++tokens, pipe_fd[1]);
			close(pipe_fd[1]);
			heredoc_fds[i] = pipe_fd[0];
		}
		tokens++;
	}
	return (heredoc_fds);
}
