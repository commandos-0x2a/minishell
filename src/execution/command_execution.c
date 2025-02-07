/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/07 19:36:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipex_handler(int is_pipe, int in_fd, int *pipefd)
{
	if (is_pipe)
		close(pipefd[0]);
	if (in_fd > 0)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror(NAME"pipex dup2 to STDIN");
			return (-1);
		}
		if (close(in_fd) == -1)
			perror(NAME"pipex close (in_fd)");
	}
	if (is_pipe)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror(NAME"pipex dup2 to STDOUT");
			return (-1);
		}
		if (close(pipefd[1]) == -1)
			perror(NAME"pipex close (pipefd[1])");
	}
	return (0);
}

static void	run_command(char **argv)
{
	char		full_path[PATH_MAX];
	extern char	**environ;
	int			err;

	if (!argv) // command not exist
		exit(0);
	// Check if the first character of the command is an opening parenthesis
	if ((*argv)[0] == '(')
	{
		(*argv)[ft_strlen(*argv) - 1] = '\0';
		(*argv)++;
		exit(flow_control(*argv));
	}
	// Allocate memory for argv.
	argv_expander(argv);

	// make malloc for argv
	argv = handle_wildcards(argv);
	if (!argv)
	{
		perror(NAME": wildcards allocate");
		exit(-1);
	}
	// Check for built-in commands before getting full path and executing.
	if (is_builtin(argv[0]))
		handle_builtin(argv, 1);
	err = get_full_path(full_path, argv, "");
	if (err == 0)
	{
		execve(full_path, argv, environ);
		perror(NAME);
		err = 1;
	}
	exit(err);
}

int command_execution(char **tokens, int in_fd, int *out_fd, int is_pipe, int prev_is_pipe)
{
	int			pid;
	int			pipefd[2];
	int			here_doc_fd;

	here_doc_fd = here_doc(tokens);
	if (here_doc_fd == -2)
		return (-1);

	// Run built-in parent.
	if (!is_pipe && !prev_is_pipe && is_builtin(get_argv0(tokens)) == 1)
	{
		redirection_handler(tokens, here_doc_fd, 0);
		if (here_doc_fd > -1)
		close(here_doc_fd);
		return (handle_builtin(get_argv(tokens), 0));
	}

	*out_fd = 0;
	if (is_pipe && pipe(pipefd) == -1)
		return (-1);

	// Fork and return pid to parent process.
	pid = fork();
	if (pid != 0)
	{
		/* ========== Parent Process ==========*/
		// Close unused file descriptors.
		if (in_fd > 0)
			close(in_fd);
		if (is_pipe)
		{
			close(pipefd[1]);
			*out_fd = pipefd[0];
			if (pid == -1)
			{
				close(pipefd[0]);
				*out_fd = 0;
			}
		}
		return (pid);
		/* ========== Bye parent ==========*/
    }
	
	/* ========== Child Process ========== */
	if (pipex_handler(is_pipe, in_fd, pipefd) != 0)
		exit(1);

	if (redirection_handler(tokens, here_doc_fd, 1) != 0)
		exit(-1);
	run_command(get_argv(tokens));
	exit(1);
}
