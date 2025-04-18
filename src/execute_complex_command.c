/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_complex_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/18 14:27:47 by yaltayeh         ###   ########.fr       */
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

static int	handle_file_descriptor(t_mini *mini, int in_fd, \
									int pipefds[2], int is_pipe)
{
	int	heredoc_fd;
	int	err;

	heredoc_fd = heredoc_forever(mini, mini->tokens);
	if (heredoc_fd < 0)
		return (-1);
	kill(getpid(), SIGSTOP);
	if (g_sig != 0)
		return (-1);
	reset_signals();

	if (pipex_handler(is_pipe, in_fd, pipefds) != 0)
		return (-1);
	err = redirection_handler(mini, heredoc_fd, 1);
	if (heredoc_fd > 0)
		close(heredoc_fd);
	if (err != 0)
		return (err);
	return (0);
}

void	exit_handler(t_mini *mini, int exit_status)
{
	mini_clean(mini);
	if (g_sig != 0)
		exit(128 + g_sig);
	exit(exit_status);
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
		g_sig = 0;
		if (handle_file_descriptor(mini, in_fd, pipefds, is_pipe) != 0)
			exit_handler(mini, EXIT_FAILURE);
		
		get_argv(&mini->tokens);
		if (!mini->tokens)
			exit_handler(mini, EXIT_FAILURE);
		execute_simple_command(mini);
		PRINT_ALLOCATE_ERROR;	
		exit_handler(mini, EXIT_FAILURE);
	}
	if (is_pipe & IS_NEXT_PIPE)
		close(pipefds[1]);
	if (is_pipe & IS_PREV_PIPE)
		close(in_fd);
	return (pid);
}
