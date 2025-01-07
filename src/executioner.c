/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/07 22:56:52 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Modify exec_command to handle parent builtins
int exec_command(char **tokens, int in_fd, int *out_fd, int is_pipe)
{
    char		full_path[PATH_MAX];
	extern char	**environ;
	int			pid;
	char		**argv;
	int			pipefd[2];

	*out_fd = 0;
	argv = NULL;

	if (is_pipe && pipe(pipefd) == -1)
		return (-1);


	// make fork and return pid to parent process
	pid = fork();
	if (pid != 0)
	{
		// close all unused fd in parent
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
	}

	/* ========== Child process ==========*/	

	// close unused read pipe_fd
	if (is_pipe)
		close(pipefd[0]);

	// connect with previous command pipe
	if (in_fd > 0)
	{
		if (dup2(in_fd, STDIN_FILENO))
			perror(NAME"pipe dup2 to STDIN");
		if (close(in_fd))
			perror(NAME"pipe close to in_fd");
	}

	// connect with next command pipe
	if (is_pipe)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			perror(NAME"pipe dup2 to STDOUT");
		if (close(pipefd[1]) == -1)
			perror(NAME"pipe close to pipefd[1]");
	}

	int	status;
	argv = redirection_handler(tokens, 1, &status);
	if (!argv) // don't find the command or failed system call
		exit(status);

	// handle sub shell
	if ((*argv)[0] == '(')
	{
		(*argv)[ft_strlen(*argv) - 1] = '\0';
		(*argv)++;
		flow_control(*argv);
		exit(1);
	}

	// Handle quotes for remaining arguments
	argv_expander(argv);

	// Check for built-in commands before get full path and execve
	// if (argv[0] && is_builtin(argv[0]))
	// 	exit(handle_builtin(argv));

	int err = get_full_path(full_path, argv, "");
	if (err == 0)
	{
		execve(full_path, argv, environ);
		perror(NAME);
		exit(1);
	}
	exit(err);
}

char	**get_next_exec(char **tokens, int *is_pipe)
{
	*is_pipe = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "|") == 0)
		{
			*is_pipe = 1;
			break ;
		}
		tokens++;
	}
	return (tokens);
}

int	here_doc_handler(char **tokens, int *fd)
{
	*fd = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0)
		{
			if (*fd > 0)
				close(*fd);
			if (run_here_doc_process(*++tokens, fd) == -1)
				return (-1);
		}
		else if (ft_strncmp(*tokens, "<<", 2) == 0)
		{
			if (*fd > 0)
				close(*fd);
			if (run_here_doc_process(*tokens + 2, fd) == -1)
				return (-1);
		}
		tokens++;
	}
	return (0);
}

int	executioner(char **tokens)
{
	char	**next_exec;
	int		is_pipe;
    int     fd;

	tokens = handle_wildcards(tokens);
    if (!tokens)
        return (-1);

	fd = 0;
	while (*tokens)
	{
		next_exec = get_next_exec(tokens, &is_pipe);

		*next_exec = NULL;

		if (is_pipe && *++next_exec == NULL)
			return (-1); // syntax error
		
		if (here_doc_handler(tokens, &fd) != 0)
			return (-1);

		// if pipe not exist run build in command in parent
		// if (!is_pipe && is_builtin_function(get_argv0(tokens)))
		// {
		// 	handle_builtin();
		// }
		
		if (exec_command(tokens, fd, &fd, is_pipe) == -1)
			return (-1);

		tokens = next_exec;
	}
	while (wait(NULL) != -1)
		;
	return (0);
}
