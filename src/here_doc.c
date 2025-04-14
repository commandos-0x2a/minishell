/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 20:43:02 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

/*
** Tracks whether the heredoc has been interrupted by SIGINT (Ctrl+C)
** @param set_value Value to set if is_setter is 1
** @param is_setter 1 to set the value, 0 to just return the current value
** @return Current interrupt status
*/
// static int	is_heredoc_interrupted(int set_value, int is_setter)
// {
// 	static int	interrupted = 0;

// 	if (is_setter)
// 		interrupted = set_value;
// 	return (interrupted);
// }

/*
** Signal handler for SIGINT during heredoc input
*/
// void	handle_heredoc_sigint(int sig)
// {
// 	(void)sig;
// 	if (heredoc_is_active())
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		is_heredoc_interrupted(1, 1);
// 	}
// }

/*
** Sets up signal handling specifically for heredoc mode
*/
// static void	setup_heredoc_signals(void)
// {
// 	struct sigaction	sa_int;

// 	is_heredoc_interrupted(0, 1);
// 	sa_int.sa_handler = handle_heredoc_sigint;
// 	sigemptyset(&sa_int.sa_mask);
// 	sa_int.sa_flags = 0;
// 	sigaction(SIGINT, &sa_int, NULL);
// }

/*
** Handles error and cleanup when heredoc is interrupted or encounters an error
*/
static int	handle_heredoc_error(t_mini *mini,char *line)
{
	(void) mini;
	// set_heredoc_active(0);
	if (line)
		free(line);
	// setup_signals();
	// mini->is_interupted = 1;
	// mini->exit_status = 130;
	return (-1);
}

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

	// set_heredoc_active(1);
	// setup_heredoc_signals();
	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			if (handle_heredoc_eof(limiter))
				break ;
		}
		process_result = process_heredoc_line(mini, line, limiter, out_fd);
		if (process_result != 0)
		{
			if (process_result < 0)
				return (handle_heredoc_error(mini, NULL));
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
