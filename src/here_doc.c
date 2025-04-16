/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/16 18:43:50 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

/*
** Handles EOF (end of file) during heredoc input
*/
static int	handle_heredoc_eof(char *limiter)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_fprintf(2, "\n" PREFIX ": warning: here-document delimited by "
			"end-of-file (wanted `%s`)\n", limiter);
	return (1);
}

/*
** Processes a line read during heredoc input
** Returns 1 if limiter is matched, 0 to continue, -1 on error
*/
static int	process_heredoc_line(t_mini *mini, char *line, char *limiter,
		int out_fd)
{
	char	*line_expand;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	if (ft_strncmp(line, limiter, limiter_len) == 0
		&& (line[limiter_len] == '\n' || line[limiter_len] == '\0'))
	{
		free(line);
		return (1);
	}
	line_expand = expand_str(mini, line);
	free(line);
	if (!line_expand)
		return (-1);
	write(out_fd, line_expand, ft_strlen(line_expand));
	free(line_expand);
	return (0);
}

/*
** Main heredoc reading function
** Handles input for a heredoc until delimiter is reached
*/
int	heredoc_start_read(t_mini *mini, char *limiter, int out_fd)
{
	char	*line;
	int		process_result;

	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			handle_heredoc_eof(limiter);
			break ;
		}
		process_result = process_heredoc_line(mini, line, limiter, out_fd);
		if (process_result != 0)
		{
			if (process_result < 0)
				return (-1);
			break ;
		}
	}
	return (0);
}

/*
** Sets up and processes multiple heredocs in a command
*/
int	heredoc_forever(t_mini *mini, t_list *lst)
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
			if (heredoc_start_read(mini, lst->str, pipefd[1]) != 0)
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
