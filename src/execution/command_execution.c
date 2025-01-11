/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 18:03:18 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipex_handler(int is_pipe, int in_fd, int *pipefd)
{
	// Close unused read pipe_fd.
	if (is_pipe)
		close(pipefd[0]);

	// Connect with previous command pipe.
	if (in_fd > 0)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror(NAME"pipe dup2 to STDIN");
			return (-1);
		}
		if (close(in_fd) == -1)
		{
			perror(NAME"pipe close to in_fd");
			return (-1);
		}
	}

	// Connect with next command pipe.
	if (is_pipe)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror(NAME"pipe dup2 to STDOUT");
			return (-1);
		}
		if (close(pipefd[1]) == -1)
		{
			perror(NAME"pipe close to pipefd[1]");
			return (-1);
		}
	}
	return (0);
}

static void run_command(char **argv)
{
	// try to change the signals for the child process before executing the command
	// set_signals_child();
	char		full_path[PATH_MAX];
	extern char	**environ;

	if (!argv) // command not exist
		exit(0);
	// Check if the first character of the command is an opening parenthesis
	if ((*argv)[0] == '(')
	{
		(*argv)[ft_strlen(*argv) - 1] = '\0';
		(*argv)++;
		exit(flow_control(*argv));
	}
	// Handle quotes for remaining arguments.
	// Handle quotes for remaining arguments.
	// Allocate memory for argv.
	argv_expander(argv);

	// make malloc for argv
	argv = handle_wildcards(argv);
	if (!argv)
	{
		perror(NAME": wildcards");
		exit(-1);
	}

	// Check for built-in commands before getting full path and executing.
	if (is_builtin(argv[0]))
	{
		int exit_status = handle_builtin(argv, 1);
		exit(exit_status);
	}

	int err = get_full_path(full_path, argv, "");
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

	in_fd = here_doc(tokens, in_fd);
	if (in_fd == -1)
		return (-1);

	// Run built-in parent.
	if (!is_pipe && !prev_is_pipe && is_builtin(get_argv0(tokens)) == 1)
	{
		redirection_handler(tokens, 0);
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

	if (redirection_handler(tokens, 1) != 0)
	{
		perror(NAME": redirection_handler");
		exit(-1);
	}
	run_command(get_argv(tokens));
	exit(1);
}
