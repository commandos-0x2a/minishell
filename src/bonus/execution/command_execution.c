/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/21 18:42:35 by yaltayeh         ###   ########.fr       */
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

static void	run_subshell(char *subshell_line)
{
	char	*line;

	line = subshell_line;
	line[ft_strlen(line) - 1] = '\0';
	line++;
	line = ft_strdup(line);
	if (!line)
	{
		PRINT_ALLOCATE_ERROR;
		exit(1);
	}
	exit(flow_control(line));
}

static int	run_builtin_command(char **tokens)
{
	// if (redirection_handler(tokens, 0) != 0)
	// 	return (1);
	return (handle_builtin(get_argv(tokens), 0));
}

char	**copy_dptr(char **dptr)
{
	char	**ptr;
	char	**new_dptr;

	ptr = dptr;
	while (*ptr)
		ptr++;
	new_dptr = ft_calloc(ptr - dptr + 1, sizeof(char *));
	if (!new_dptr)
		return (NULL);
	ptr = new_dptr;
	while (*dptr)
		*ptr++ = *dptr++;
	return (new_dptr);
}

char	**copy_used_tokens(t_tokens *tok, char **used_tokens)
{
	int		i;
	int		j;

	i = 0;
	while (i < tok->nb_tokens)
	{
		j = 0;
		while (used_tokens[j] && tok->tokens[i])
		{
			if (tok->tokens[i] == used_tokens[j])
				break;
			j++;
		}
		if (!used_tokens[j] && tok->tokens[i])
		{
			free(tok->tokens[i]);
			tok->tokens[i] = NULL;
		}
		i++;
	}
	used_tokens = copy_dptr(used_tokens);
	free(tok->tokens);
	return (used_tokens);
}

static void	run_command(char **argv)
{
	char		full_path[PATH_MAX];
	int			err;

	if (!*argv) // command not exist
		exit(0);
		
	// Check if the first character of the command is an opening parenthesis
	if ((*argv)[0] == '(')
		run_subshell(*argv);
	
	argv = argv_expander(argv);
	if (!argv)
	{
		PRINT_ALLOCATE_ERROR;
		exit(-1);
	}
	argv = handle_wildcards(argv);
	if (!argv)
	{
		PRINT_ALLOCATE_ERROR;
		exit(-1);
	}
	// Check for built-in commands before getting full path and executing.
	if (is_builtin(argv[0]))
		handle_builtin(argv, 1);
	err = get_full_path(full_path, argv, "");
	if (err == 0)
	{
		execve(full_path, argv, *__init__env());
		cleanup_env_copy();
		perror(PREFIX"execve");
		err = 1;
	}
	exit(err);
}

int command_execution(char **tokens, int *fd, int is_pipe)
{
	int		pid;
	int		pipefd[2];
	char	**argv;
	int		heredoc_fd;
	
	// Run built-in in parent.
	if ((is_pipe & IS_PIPE_MASK) == 0 && is_builtin(get_argv0(tokens)) == 1)
		return (run_builtin_command(tokens));


	if ((is_pipe & IS_PIPE) && pipe(pipefd) == -1)
	{
		if (is_pipe & IS_PREV_PIPE)
		{
			close(*fd);
			*fd = -1;
		}
		return (-1);
	}



	pid = fork();
	if (pid == 0)
	{
		/* ========== Child Process ========== */
		if (is_pipe)
			close(pipefd[0]);
		heredoc_fd = heredoc_forever(tokens);
		
		kill(getpid(), SIGSTOP); 
		
		if (redirection_handler(tokens, heredoc_fd, 1) != 0)
		{
			exit(126);
		}
		close(heredoc_fd);
		if (pipex_handler(is_pipe, *fd, pipefd) != 0)
		{
			exit(1);
		}

		argv = get_argv(tokens);
		// argv = copy_used_tokens(tok, argv);
		if (!argv)
			exit(1);

		run_command(argv);
		exit(1);
	}
	/* ========== Parent Process ==========*/
	// Close unused file descriptors from previous pipe.
	if (is_pipe & IS_PREV_PIPE)
		close(*fd);
	*fd = -1;
	if (is_pipe & IS_PIPE)
	{
		close(pipefd[1]);
		*fd = pipefd[0];
		if (pid == -1)
		{
			close(*fd);
			*fd = -1;
		}
	}
	return (pid);
}
