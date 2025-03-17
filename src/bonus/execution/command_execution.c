/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/17 12:47:20 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	pipex_handler(int is_pipe, int in_fd, int *pipefd)
{
	if (is_pipe)
		close(pipefd[0]);
	if (is_pipe & IS_PREV_PIPE)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror(PREFIX"pipex dup2 to STDIN");
			return (-1);
		}
		if (close(in_fd) == -1)
			perror(PREFIX"pipex close (in_fd)");
	}
	if (is_pipe & IS_PIPE)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror(PREFIX"pipex dup2 to STDOUT");
			return (-1);
		}
		if (close(pipefd[1]) == -1)
			perror(PREFIX"pipex close (pipefd[1])");
	}
	return (0);
}

static void	run_command(t_tokens *tok, char **argv)
{
	char		full_path[PATH_MAX];
	extern char	**environ;
	int			err;
	char		*tmp;

	if (!argv) // command not exist
		exit(0);
	// Check if the first character of the command is an opening parenthesis
	if ((*argv)[0] == '(')
	{
		tmp = *argv;
		tmp[ft_strlen(tmp) - 1] = '\0';
		tmp++;
		tmp = ft_strdup(tmp);
		free_tokens(tok);
		if (!tmp)
		{
			perror(PREFIX"allocate subshell line");
			exit(1);
		}
		exit(flow_control(tmp));
	}

	argv = argv_expander(argv);
	free_tokens(tok);
	if (!argv)
	{
		perror(PREFIX"wildcards expander");
		exit(-1);
	}
	argv = handle_wildcards(argv);
	if (!argv)
	{
		perror(PREFIX"wildcards allocate");
		exit(-1);
	}
	// Check for built-in commands before getting full path and executing.
	if (is_builtin(argv[0]))
		handle_builtin(tok, argv, 1);
	err = get_full_path(full_path, argv, "");
	if (err == 0)
	{
		execve(full_path, argv, environ);
		perror(PREFIX"execve");
		err = 1;
	}
	exit(err);
}

static int	run_builtin_command(t_tokens *tok, char **tokens, int here_doc_fd)
{
	if (here_doc_fd > -1)
		close(here_doc_fd);
	if (redirection_handler(tokens, -1, 0) != 0)
		return (1);
	return (handle_builtin(tok, get_argv(tokens), 0));
}

void	close_unused(t_tokens *tok)
{
	int	i;

	i = tok->i + 1; // skip current
	while (i < tok->nb_heredoc)
	{
		if (tok->heredoc_fds[i] > -1)
			close(tok->heredoc_fds[i]);
		i++;
	}
}

int command_execution(t_tokens *tok, char **tokens, int *fd, int is_pipe)
{
	int	pid;
	int	pipefd[2];
	int	here_doc_fd;
	
	here_doc_fd = tok->heredoc_fds[tok->i];
	tok->heredoc_fds[tok->i] = -1;

	
	// Run built-in in parent.
	if ((is_pipe & IS_PIPE_MASK) == 0 && is_builtin(get_argv0(tokens)) == 1)
		return (run_builtin_command(tok, tokens, here_doc_fd));
	

		
	if ((is_pipe & IS_PIPE) && pipe(pipefd) == -1)
	{
		if (is_pipe & IS_PREV_PIPE)
		{
			close(*fd);
			*fd = -1;
		}
		if (here_doc_fd > -1)
			close(here_doc_fd);
		return (-1);
	}



	pid = fork();
	if (pid == 0)
	{
		close_unused(tok);
		/* ========== Child Process ========== */
		if (pipex_handler(is_pipe, *fd, pipefd) != 0)
		{
			exit(1);
		}
		if (redirection_handler(tokens, here_doc_fd, 1) != 0)
		{
			exit(126);
		}
		run_command(tok, get_argv(tokens));
		exit(1);
	}
	/* ========== Parent Process ==========*/
	// Close unused file descriptors from previous pipe.
	if (is_pipe & IS_PREV_PIPE)
		close(*fd);
	if (here_doc_fd > -1)
		close(here_doc_fd);
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
