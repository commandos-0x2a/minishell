/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/27 20:40:37 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"
#include <sys/ioctl.h>

/*
** Processes a line read during heredoc input
** Returns 1 if limiter is matched, 0 to continue, -1 on error
*/
static int	line_cmp(char *line, char *limiter)
{
	size_t	limiter_len;

	if (!*line)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			ft_fprintf(2, "\n" PREFIX ": warning: here-document delimited by "
				"end-of-file (wanted `%s`)\n", limiter);
		free(line);
		return (0);
	}
	limiter_len = ft_strlen(limiter);
	if (ft_strncmp(line, limiter, limiter_len) == 0
		&& (line[limiter_len] == '\n' || line[limiter_len] == '\0'))
	{
		free(line);
		return (0);
	}
	return (1);
}

static int	handle_chunk(t_mini *mini, char *limiter,
						ssize_t nbytes, int out_fd)
{
	char	*line;
	char	*line_expanded;
	ssize_t	line_len;

	line = malloc(nbytes + 1);
	if (!line)
		return (-1);
	nbytes = read(STDIN_FILENO, line, nbytes);
	if (nbytes == -1)
	{
		free(line);
		return (-1);
	}
	line[nbytes] = '\0';
	if (line_cmp(line, limiter) == 0)
		return (0);
	line_expanded = expand_env(mini, line);
	free(line);
	if (!line_expanded)
		return (-1);
	line_len = ft_strlen(line_expanded);
	if (write(out_fd, line_expanded, line_len) != line_len)
		return (-1);
	free(line_expanded);
	return (1);
}

/*
** Main heredoc reading function
** Handles input for a heredoc until delimiter is reached
*/
static int	heredoc_start_read(t_mini *mini, char *limiter, int out_fd)
{
	int		err;
	int		nbytes;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDOUT_FILENO, "> ", 2);
	remove_qouts(limiter);
	while (1)
	{
		if (ioctl(STDIN_FILENO, FIONREAD, &nbytes) == -1)
			return (-1);
		if (g_sig != 0)
			return (1);
		if (nbytes > 0)
		{
			err = handle_chunk(mini, limiter, nbytes, out_fd);
			if (err <= 0)
				return (err);
			if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
				write(STDOUT_FILENO, "> ", 2);
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
