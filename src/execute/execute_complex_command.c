/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_complex_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/25 17:38:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipex_handler(int pipe_mask, int in_fd, int pipefds[2])
{
	if (pipe_mask & IS_PREV_PIPE)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			close(in_fd);
			perror(PREFIX"pipex dup2 to STDIN");
			return (-1);
		}
		close(in_fd);
	}
	if (pipe_mask & IS_NEXT_PIPE)
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

static int	stop_process(void)
{
	pid_t	victim;

	if (g_sig != 0)
		return (-1);
	victim = ft_getpid();
	if (victim < 0)
		return (-1);
	if (kill(victim, SIGSTOP) == -1)
		return (-1);
	if (g_sig != 0)
		return (-1);
	reset_signals();
	return (0);
}

static int	close_heredoc_fd(int heredoc_fd)
{
	if (heredoc_fd > 0)
		close(heredoc_fd);
	return (-1);
}

static int	handle_file_descriptor(t_mini *mini, int in_fd,
									int pipefds[2], int pipe_mask)
{
	int	heredoc_fd;
	int	err;

	heredoc_fd = heredoc_forever(mini, mini->tokens);
	if (heredoc_fd < 0)
	{
		if (g_sig == 0)
			print_error(__FILE__, __LINE__);
		if (pipe_mask & IS_PREV_PIPE)
			close(in_fd);
		if (pipe_mask & IS_NEXT_PIPE)
			close(pipefds[1]);
		return (-1);
	}
	if (pipex_handler(pipe_mask, in_fd, pipefds) != 0)
		return (close_heredoc_fd(heredoc_fd));
	if (is_subshell(mini->tokens) && subshell_syntax(mini->tokens) == 0)
		return (close_heredoc_fd(heredoc_fd));
	if (stop_process() != 0)
		return (close_heredoc_fd(heredoc_fd));
	err = redirection_handler(mini, heredoc_fd);
	close_heredoc_fd(heredoc_fd);
	if (err != 0)
		return (err);
	return (0);
}

int	execute_complex_command(t_mini *mini, int in_fd,
							int pipefds[2], int pipe_mask)
{
	int	pid;
	int	err;

	pid = fork();
	if (pid == 0)
	{
		if (pipe_mask & IS_NEXT_PIPE)
			close(pipefds[0]);
		g_sig = 0;
		if (handle_file_descriptor(mini, in_fd, pipefds, pipe_mask) != 0)
			exit_handler(mini, EXIT_FAILURE);
		get_argv(&mini->tokens);
		if (!mini->tokens)
			exit_handler(mini, EXIT_SUCCESS);
		err = execute_simple_command(mini);
		if (err == 1)
			print_error(__FILE__, __LINE__);
		exit_handler(mini, err);
	}
	if (pipe_mask & IS_NEXT_PIPE)
		close(pipefds[1]);
	if (pipe_mask & IS_PREV_PIPE)
		close(in_fd);
	return (pid);
}
