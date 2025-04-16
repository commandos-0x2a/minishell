/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_complex_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/16 18:46:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipex_handler(int is_pipe, int in_fd, int pipefds[2])
{
	if (is_pipe & IS_PREV_PIPE)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			close(in_fd);
			perror(PREFIX"pipex dup2 to STDIN");
			return (-1);
		}
		close(in_fd);
	}
	if (is_pipe & IS_NEXT_PIPE)
	{
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
		{
			close(pipefds[1]);
			perror(PREFIX"pipex dup2 to STDOUT");
			return (-1);
		}
		close(pipefds[1]);
	}
	return (0);
}

static void	handle_child_process(t_mini *mini, int in_fd, \
									int pipefds[2], int is_pipe)
{
	int	heredoc_fd;
	int	status;

	status = EXIT_FAILURE;
	heredoc_fd = heredoc_forever(mini, mini->tokens);
	if (heredoc_fd < 0)
	{
		status = mini->exit_status;
		mini_clean(mini);
		exit(status);
	}
	kill(getpid(), SIGSTOP);
	if (pipex_handler(is_pipe, in_fd, pipefds) != 0)
	{
		mini_clean(mini);
		exit(status);
	}
	if (redirection_handler(mini, heredoc_fd, 1) != 0)
	{
		mini_clean(mini);
		exit(126);
	}
	if (heredoc_fd > 0)
		close(heredoc_fd);
}

int	execute_complex_command(t_mini *mini, int in_fd, \
							int pipefds[2], int is_pipe)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (is_pipe & IS_NEXT_PIPE)
			close(pipefds[0]);
		reset_signals_child();
		handle_child_process(mini, in_fd, pipefds, is_pipe);
		
		get_argv(&mini->tokens);
		if (!mini->tokens)
		{
			mini_clean(mini);
			exit(EXIT_SUCCESS);
		}
		execute_simple_command(mini);		
		mini_clean(mini);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
