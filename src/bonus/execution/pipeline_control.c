/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/07 15:05:59 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_next_command(char **tokens, int *is_pipe)
{
	char	**next;

	next = ft_tokpbrk(tokens, "|", NULL);
	*is_pipe <<= 1;
	if (*next)
		*is_pipe |= 1;
	return (next);
}

static int	get_nb_command(char **tokens)
{
	int	nb_pipeline;

	nb_pipeline = 1;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "|") == 0)
			nb_pipeline++;
		tokens++;
	}
	return (nb_pipeline);
}

static int	run_builtin_command(t_mdata *mdata, char **tokens)
{
	int	heredoc_fd;

	heredoc_fd = heredoc_forever(tokens);
	if (heredoc_fd < 0)
		return (-1);
	if (redirection_handler(tokens, heredoc_fd, 0) != 0)
	{
		if (heredoc_fd > 0)
			close(heredoc_fd);
		return (-1);
	}
	if (heredoc_fd > 0)
		close(heredoc_fd);
	return (handle_builtin(mdata, copy_dptr(get_argv(tokens)), 0));
}

int	pipeline_control(t_mdata *mdata, char **pipeline)
{
	int		is_pipe;
	int		fd;
	char	**next_command;
	int		i;
	int		nb_commands;
	pid_t	victim_pid;

	nb_commands = get_nb_command(pipeline);
	if (nb_commands == 1 && is_builtin(get_argv0(pipeline)))
		return (run_builtin_command(mdata, pipeline));

	mdata->command_pid = ft_calloc(nb_commands, sizeof(pid_t));
	if (!mdata->command_pid)
		return (-1);
	fd = -1;
	is_pipe = 0;
	i = 0;
	while (*pipeline)
	{
		next_command = get_next_command(pipeline, &is_pipe);
		if (is_pipe & IS_PIPE)
			*next_command++ = NULL;
		mdata->command_pid[i] = execute_complex_command(mdata, pipeline, &fd, is_pipe);
		if (mdata->command_pid[i] == -1)
			break ;
		if (waitpid(mdata->command_pid[i], NULL, WUNTRACED) == -1)
			break ;
		pipeline = next_command;
		i++;
	}
	while (i--)
	{
		kill(mdata->command_pid[i], SIGCONT);
		waitpid(mdata->command_pid[i], NULL, WCONTINUED);
	}
	victim_pid = mdata->command_pid[nb_commands - 1];
	free(mdata->command_pid);
	mdata->command_pid = NULL;
	return (wait_children(victim_pid));
}
