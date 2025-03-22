/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:37:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/22 11:00:26 by yaltayeh         ###   ########.fr       */
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

static int	run_builtin_command(char **tokens)
{
	// if (redirection_handler(tokens, 0) != 0)
	// 	return (1);
	return (handle_builtin(get_argv(tokens), 0));
}

char	**copy_dptr(char **dptr)
{
	char	**ptr;
	char	**dst;

	ptr = dptr;
	while (*ptr)
		ptr++;
	dst = ft_calloc(ptr - dptr + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	ptr = dst;
	while (*dptr)
	{
		*ptr = ft_strdup(*dptr++);
		if (*ptr == NULL)
		{
			ptr = dst;
			while (*ptr)
				free(*ptr++);
			free(dst);
			return (NULL);
		}
		ptr++;
	}
	return (dst);
}

void	clean_and_exit(t_mdata *mdata, int exit_status)
{
	if (mdata->command_pid)
		free(mdata->command_pid);
	if (mdata->line)
		free(mdata->line);
	if (mdata->tokens)
		free(mdata->tokens);
	cleanup_env_copy();
	exit(exit_status);
}

// allocate:
//	- char	*line
//	- char	**tokens
//	- pid_t	*children_pid
//	- char	**env # global
int command_execution(t_mdata *mdata, char **tokens, int *fd, int is_pipe)
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
			close(*fd);
		return (-1);
	}



	pid = fork();
	if (pid == 0)
	{
		/* ========== HEAP Memory ========== */
		// allocate:
		//	- char	*line
		//	- char	**tokens
		//	- pid_t	*children_pid

		
		//	- pid_t	*children_pid
		free(mdata->command_pid);
		mdata->command_pid = NULL;
		
		/* ========== Child Process ========== */
		if (is_pipe)
			close(pipefd[0]);
		heredoc_fd = heredoc_forever(tokens);
		
		kill(getpid(), SIGSTOP); 
		
		if (redirection_handler(tokens, heredoc_fd, 1) != 0)
			clean_and_exit(mdata, 126);
		if (heredoc_fd > -1)
			close(heredoc_fd);
		if (pipex_handler(is_pipe, *fd, pipefd) != 0)
			clean_and_exit(mdata, 1);

		argv = copy_dptr(get_argv(tokens));

		// destroy mdata
		//	- char	**tokens
		free(mdata->tokens);
		mdata->tokens = NULL;
		//	- char	*line
		free(mdata->line);
		mdata->line = NULL;
		

		if (!argv)
			clean_and_exit(mdata, 1);

		run_command(argv);
		exit(1);
	}
	/* ========== Parent Process ==========*/
	// Close unused file descriptors from previous pipe.
	if (is_pipe & IS_PREV_PIPE)
		close(*fd);
	if (is_pipe & IS_PIPE)
	{
		close(pipefd[1]);
		*fd = pipefd[0];
		if (pid == -1)
			close(*fd);
	}
	return (pid);
}
