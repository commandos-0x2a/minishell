/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/07 00:42:11 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *limiter)
{
	int	fd;

	if (run_here_doc_process(limiter, &fd) == -1)
	{
		perror(NAME);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	in_redirection(char *file)
{
	int	fd;

	file = expand_str(file);
	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
	{
		perror(NAME);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	out_append(char *file)
{
	int fd;

	file = expand_str(file);
	if (!file)
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(file);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	out_redirection(char *file)
{
	int fd;

	file = expand_str(file);
	if (!file)
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (fd == -1)
	{
		perror(file);
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

// Add this helper to identify parent-only builtins
int is_parent_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "cd") == 0 ||
            ft_strcmp(cmd, "exit") == 0 ||
            ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0);
}

// Modify exec_command to handle parent builtins
int exec_command(char ***argv_p, int in_fd, int *out_fd)
{
    char **argv = *argv_p;
    
    // First check for parent-only builtins
    if (argv[0] && is_parent_builtin(argv[0]))
    {
        int original_fd = -1;
        if (check_pipe(argv_p))
        {
            ft_fprintf(2, "minishell: %s: cannot be used in a pipeline\n", argv[0]);
            return -1;
        }
        
        // Setup redirections for builtin
        if (argv[1])
            original_fd = setup_redirections(argv);
            
        int status = handle_builtin(argv);
        
        // Restore original output if needed
        if (original_fd != -1)
            restore_output(original_fd);
            
        return status;
    }

    // Rest of existing exec_command code
    char		full_path[PATH_MAX];
	extern char	**environ;
	int			i;
	int			pid;
	char		**cmd_argv;
	int			pipefd[2];
	int			is_pipe;

	*out_fd = 0;

	cmd_argv = NULL;

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

	// set pipe arg "NULL"
	**argv_p = NULL;

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

	// Handle redirections first
	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(*argv, "<<") == 0)
		{
			*argv = NULL;
			here_doc(*(++argv));
		}
		else if (ft_strncmp(*argv, "<<", 2) == 0)
		{
			here_doc(*argv + 2);
			*argv = NULL;
		}
		else if (ft_strcmp(*argv, "<") == 0)
		{
			*argv = NULL;
			in_redirection(*++argv);
		}
		else if (ft_strncmp(*argv, "<", 1) == 0)
		{
			in_redirection(*argv + 1);
			*argv = NULL;
		}
		else if (ft_strcmp(*argv, ">>") == 0)
		{
			*argv = NULL;
			out_append(*++argv);
		}
		else if (ft_strncmp(*argv, ">>", 2) == 0)
		{
			out_append(*argv + 2);
			*argv = NULL;
		}
		else if (ft_strcmp(*argv, ">") == 0)
		{
			*argv = NULL;
			out_redirection(*++argv);
		}
		else if (ft_strncmp(*argv, ">", 1) == 0)
		{
			out_redirection(*argv + 1);
			*argv = NULL;
		}
		else if (!cmd_argv)
			cmd_argv = argv;


		argv++; // next token
	}

	// exit if don't find command
	if (!cmd_argv)
		exit(0);

	// handle sub shell
	if ((*cmd_argv)[0] == '(')
	{
		(*cmd_argv)[ft_strlen(*cmd_argv) - 1] = '\0';
		(*cmd_argv)++;
		executioner(*cmd_argv);
		exit(1);
	}

	// Handle quotes for remaining arguments
	argv_expander(cmd_argv);

	// Check for built-in commands before get full path and execve
	if (cmd_argv[0] && is_builtin(cmd_argv[0]))
		exit(handle_builtin(cmd_argv));

	int err = get_full_path(full_path, cmd_argv, "");
	if (err == 0)
	{
		execve(full_path, cmd_argv, environ);
		perror(NAME);
		exit(1);
	}
	exit(err);
}

int	executioner(char *line)
{
    char    **argv;
    char    **ptr;
    int     fd;

    argv = tokenizer(line, 0);
    if (!argv)
        return (0);

    argv = handle_wildcards(argv);
    if (!argv)
        return (-1);

	ptr = argv;
	fd = 0;
	while (*ptr)
	{
		if (exec_command(&ptr, fd, &fd) == -1)
			return (-1);
		if (!*ptr)
			break;
		ptr++;
	}
	free(argv);
	while (wait(NULL) != -1)
		;
	return (0);
}
