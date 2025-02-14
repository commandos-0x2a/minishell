/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/13 22:01:19 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_next_command(char **tokens, int *is_pipe)
{
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "|") == 0)
		{
			*is_pipe <<= 1;
			*is_pipe |= 1;
			break ;
		}
		tokens++;
	}
	return (tokens);
}

int	pipeline_check_syntax(char **tokens)
{
	char	**next_command;
	int		is_pipe;

	is_pipe = 0;
	while (*tokens)
	{
		next_command = get_next_command(tokens, &is_pipe);
		if ((is_pipe & IS_PIPE) && *++next_command == NULL)
		{
			ft_fprintf(2, NAME": syntax error `|'\n");
			return (-1);
		}
		tokens = next_command;
	}
	return (0);
}

int	pipeline_control(t_tokens *tok, char **pipeline)
{
	int		is_pipe;
	int		fd;
	int		proc_pid;
	char	**next_command;

	fd = -1;
	proc_pid = 0;
	is_pipe = 0;
	while (*pipeline)
	{
		next_command = get_next_command(pipeline, &is_pipe);
		if (is_pipe & IS_PIPE)
			*next_command++ = NULL;
		proc_pid = command_execution(tok, pipeline, &fd, is_pipe);
		if (proc_pid == -1)
			break ;
		pipeline = next_command;
	}
	return (wait_children(proc_pid));
}
