/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/17 19:59:24 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

/*

static void handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		// exit(130);
	}
}

static int setup_heredoc_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_heredoc_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	return (0);
}

	*heredoc_active() = 1;
	save_signal_handlers();
	if (setup_heredoc_signals() == -1)
	{
		*heredoc_active() = 0;
		restore_signal_handlers();
		return (-1);
	}

	...
	
	*heredoc_active() = 0;
	restore_signal_handlers();
*/

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
				ft_fprintf(2, "\n" NAME ": warning: " \
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

int	here_doc(char **tokens, int *here_doc_fd)
{
	int	pipe_fd[2];

	*here_doc_fd = -1;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0)
		{
			if (*here_doc_fd > -1)
				close(*here_doc_fd);
			if (pipe(pipe_fd) == -1)
			{
				perror(NAME": pipe here doc");
				return (-1);
			}
			here_doc_start_read(*++tokens, pipe_fd[1]);
			close(pipe_fd[1]);
			*here_doc_fd = pipe_fd[0];
		}
		tokens++;
	}
	return (0);
}
