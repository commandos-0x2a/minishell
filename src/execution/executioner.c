/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/09 19:44:56 by yaltayeh         ###   ########.fr       */
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
		/* ========== Parent process ==========*/
		// close unused fd
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

	if (redirection_handler(tokens, 1) != 0)
	{
		perror(NAME": redirection_handler");
		exit(-1);
	}
	argv = get_argv(tokens);
	if (!argv) // command not exist
		exit(0);


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

	argv = handle_wildcards(argv);
	if (!argv)
	{
		perror(NAME": wildcards");
		exit(-1);
	}
	// Check for built-in commands before get full path and execve
	if (is_builtin(argv[0]))
		handle_builtin(argv, 1);

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

int	here_doc_handler(char **tokens, int fd)
{
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0)
		{
			if (fd > 0)
				close(fd);
			fd = here_doc(*++tokens);
			if (fd == -1)
			{
				perror(NAME": here_doc");
				return (-1);
			}
		}
		else if (ft_strncmp(*tokens, "<<", 2) == 0)
		{
			if (fd > 0)
				close(fd);
			fd = here_doc(*tokens + 2);
			if (fd == -1)
			{
				perror(NAME": here_doc");
				return (-1);
			}
		}
		tokens++;
	}
	return (fd);
}

int	executioner(char **tokens)
{
	char	**next_exec;
	int		is_pipe;
	int		prev_is_pipe;
    int     fd;
	int		proc_pid;

	fd = 0;
	prev_is_pipe = 0;
	proc_pid = -1;
	while (*tokens)
	{
		next_exec = get_next_exec(tokens, &is_pipe);

		*next_exec = NULL;

		if (is_pipe && *++next_exec == NULL)
		{
			ft_fprintf(2, NAME": syntax error `|'\n");
			return (-1); // syntax error
		}
		fd = here_doc_handler(tokens, fd);
		if (fd == -1)
			return (-1);

		if (!is_pipe && !prev_is_pipe && is_builtin(get_argv0(tokens)) == 1)
		{
			if(redirection_handler(tokens, 0) != 0)
			{
				perror("redirection_handler");
				return (-1);
			}
			tokens = get_argv(tokens);
			return (handle_builtin(tokens, 0));
		}
		else 
		{
			proc_pid = exec_command(tokens, fd, &fd, is_pipe);
			if (proc_pid == -1)
				return (-1);
		}
		prev_is_pipe = is_pipe;
		tokens = next_exec;
	}
	return (wait_children(proc_pid));
}
