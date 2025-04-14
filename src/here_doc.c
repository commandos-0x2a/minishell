/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 06:23:49 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

int	heredoc_start_read(t_list *env, char *limiter, int out_fd)
{
	char	*line;
	char	*line_expand;
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
		line_expand = expand_str(env, line);
		free(line);
		if (!line_expand)
			return (-1);
		write(out_fd, line_expand, ft_strlen(line_expand));
	}
	return (0);
}

int	heredoc_forever(t_list *lst, t_list *env)
{
	int	fd;
	int	pipefd[2];

	fd = 0;
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "<<") == 0)
		{
			lst = lst->next;
			if (fd > 0)
				close(fd);
			if (pipe(pipefd) == -1)
				return (-1);
			if (heredoc_start_read(env, lst->str, pipefd[1]) != 0)
			{
				close(pipefd[0]);
				close(pipefd[1]);
				return (-1);
			}
			close(pipefd[1]);
			fd = pipefd[0];
		}
		lst = lst->next;
	}
	return (fd);
}
