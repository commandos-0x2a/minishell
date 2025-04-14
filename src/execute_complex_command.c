/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_complex_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 15:43:44 by mkurkar          ###   ########.fr       */
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

static void	handle_child_process(t_mini *mini, int *fd, int is_pipe, int *pipefd)
{
	int	heredoc_fd;

	if (is_pipe & IS_PIPE)
		close(pipefd[0]);
	heredoc_fd = heredoc_forever(mini, mini->tokens);
	if (heredoc_fd < 0)
	{
		mini_clean(mini);
		exit(EXIT_FAILURE);
	}
	kill(getpid(), SIGSTOP);
	if (pipex_handler(is_pipe, *fd, pipefd) != 0)
	{
		mini_clean(mini);
		exit(EXIT_FAILURE);
	}
	if (redirection_handler(mini, heredoc_fd, 1) != 0)
	{
		mini_clean(mini);
		exit(126);
	}
	if (heredoc_fd > 0)
		close(heredoc_fd);
}

static void	prepare_and_execute_command(t_mini *mini)
{
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

static void	handle_parent_process(int is_pipe, int *fd, int *pipefd, int pid)
{
	if (is_pipe & IS_PREV_PIPE)
		close(*fd);
	if (is_pipe & IS_PIPE)
	{
		close(pipefd[1]);
		*fd = pipefd[0];
		if (pid == -1)
			close(*fd);
	}
}

int	execute_complex_command(t_mini *mini, int *fd, int is_pipe)
{
	int	pid;
	int	pipefd[2];

	if ((is_pipe & IS_PIPE) && pipe(pipefd) == -1)
	{
		if (is_pipe & IS_PREV_PIPE)
			close(*fd);
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		handle_child_process(mini, fd, is_pipe, pipefd);
		prepare_and_execute_command(mini);
	}
	handle_parent_process(is_pipe, fd, pipefd, pid);
	return (pid);
}
