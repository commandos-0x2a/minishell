/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/06 17:43:20 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *limiter)
{
	int	fd;

	if (run_here_doc_process(limiter, &fd) == -1)
	{
		perror("minishell");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	in_redirection(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	out_append(char *outfile)
{
	int fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(outfile);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	out_redirection(char *outfile)
{
	int fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(outfile);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	check_pipe(char ***argv_p)
{
	char	**argv;

	argv = *argv_p;
	while (*argv)
	{
		if (ft_strcmp(*argv, "|") == 0)
		{
			*argv_p = argv;
			return (1);
		}
		argv++;
	}
	*argv_p = argv;
	return (0);
}

int	exec_command(char ***argv_p, int in_fd, int *out_fd)
{
	char		full_path[PATH_MAX];
	extern char	**environ;
	int			i;
	char		*ptr;
	int			pid;
	char		**cmd_argv;
	char		**argv;
	int			pipefd[2];
	int			is_pipe;

	*out_fd = 0;

	cmd_argv = NULL;
	argv = *argv_p;

	is_pipe = check_pipe(argv_p);

	if (is_pipe && !**argv_p)
	{
		fprintf(stderr, "syntax error '|' \n");
		return (-1);
	}
	if (is_pipe && pipe(pipefd) == -1)
		return (-1);


	// make fork and return pid to parent process
	pid = fork();
	if (pid != 0)
	{		
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

	**argv_p = NULL;

	// close unused read pipe_fd
	if (is_pipe)
		close(pipefd[0]);


	// connect with previous command
	if (in_fd > 0)
	{
		if (dup2(in_fd, STDIN_FILENO))
			perror("pipe dup2 to STDIN");
		if (close(in_fd))
			perror("pipe close to in_fd");
	}

	// connect with next command
	if (is_pipe)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			perror("pipe dup2 to STDOUT");
		if (close(pipefd[1]) == -1)
			perror("pipe close to pipefd[1]");
	}

	// Handle redirections first
	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "<<", 2) == 0)
		{
			if (ft_strlen(argv[i]) == 2)
				ptr = argv[++i];
			else
				ptr = argv[i++] + 2;
			here_doc(ptr);
			argv[i - 1] = NULL;
			continue;
		}
		else if (ft_strncmp(argv[i], "<", 1) == 0)
		{
			if (ft_strlen(argv[i]) == 1)
				ptr = argv[++i];
			else
				ptr = argv[i++] + 1;
			in_redirection(ptr);
			argv[i - 1] = NULL;
			continue;
		}
		else if (ft_strncmp(argv[i], ">>", 2) == 0)
		{
			if (ft_strlen(argv[i]) == 2)
				ptr = argv[++i];
			else
				ptr = argv[i++] + 2;
			out_append(ptr);
			argv[i - 1] = NULL;
		}
		else if (ft_strncmp(argv[i], ">", 1) == 0)
		{
			if (ft_strlen(argv[i]) == 1)
				ptr = argv[++i];
			else
				ptr = argv[i++] + 1;
			out_redirection(ptr);
			argv[i - 1] = NULL;
		}
		else if (!cmd_argv)
			cmd_argv = argv + i;
		i++;
	}

	// exit if don't find command
	if (!cmd_argv)
		exit(0);

	// Handle quotes for remaining arguments
	argv_expander(cmd_argv);

	// Check for built-in commands before get full path and execve
	if (cmd_argv[0] && is_builtin(cmd_argv[0]))
		exit(handle_builtin(cmd_argv));

	int err = get_full_path(full_path, cmd_argv, "");
	if (err == 0)
	{
		execve(full_path, cmd_argv, environ);
		perror("minishell");
		exit(1);
	}
	exit(err);
}

int	executioner(char *line, int indent)
{
	char	**argv;
	char	**ptr;
	// int		i = 0;
	int		fd;

	argv = tokenizer(line, 0);
	if (!argv)
		return (0);

	// Add wildcard expansion here
	argv = handle_wildcards(argv);
	if (!argv)
		return (-1);

	ptr = argv;
	fd = 0;
	while (*ptr)
	{
		(void)indent;
		// if ((*ptr)[0] == '(')
 		// if ((*ptr)[0] == '(')
		// {
		// 	(*ptr)[ft_strlen(*ptr) - 1] = '\0'; // remove ')'
		// 	tokenizer(*ptr + 1 /* skip '(' */, indent + 4);
		// }
		// else
		// {
			// if (ft_strcmp(*ptr, "&&") == 0)
			// 	fprintf(stderr, "%-*s%i: AND\n", indent, "", i);
			// else if (ft_strcmp(*ptr, "||") == 0)
			// 	fprintf(stderr, "%-*s%i: OR\n", indent, "", i);
			// else
				if (exec_command(&ptr, fd, &fd) == -1)
					return (-1);
		// }
		if (!*ptr)
			break;
		ptr++;
	}
	free(argv);
	while (wait(NULL) != -1)
		;
	return (0);
}
