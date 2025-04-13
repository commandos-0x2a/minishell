/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_complex_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 02:02:06 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipex_handler(int is_pipe, int in_fd, int *pipefd)
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
	if (is_pipe & IS_PIPE)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			close(pipefd[1]);
			perror(PREFIX"pipex dup2 to STDOUT");
			return (-1);
		}
		close(pipefd[1]);
	}
	return (0);
}

int execute_complex_command(t_mini *mini, int *fd, int is_pipe)
{
	int		pid;
	int		pipefd[2];
	int		heredoc_fd;

	if ((is_pipe & IS_PIPE) && pipe(pipefd) == -1)
	{
		if (is_pipe & IS_PREV_PIPE)
			close(*fd);
		return (-1);
	}

	pid = fork();
	if (pid == 0) /* ========== Child Process ========== */
	{
		/* ========== HEAP Memory ========== */
		if (is_pipe & IS_PIPE)
			close(pipefd[0]);

		heredoc_fd = heredoc_forever(mini->tokens);
		if (heredoc_fd < 0)
			exit(1);

		kill(getpid(), SIGSTOP);
		
		if (pipex_handler(is_pipe, *fd, pipefd) != 0)
			exit(1);
		
		if (redirection_handler(mini->tokens, heredoc_fd, 1) != 0)
			exit(126);
		if (heredoc_fd > 0)
			close(heredoc_fd);
		get_argv(&mini->tokens);
		if (!mini->tokens)
			exit(0);

		execute_simple_command(mini);
		exit(1);
	}
	/* ========== Parent Process ==========*/
	// Close unused file descriptors from previous pipe.
	if (is_pipe & IS_PREV_PIPE)
		close(*fd);
	if (is_pipe & IS_PIPE)
	{
		close(pipefd[1]);
		*fd = pipefd[0];
		if (pid == -1)
			close(*fd);
	}
	return (pid);
}
