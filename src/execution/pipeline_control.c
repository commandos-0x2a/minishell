/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/07 15:35:54 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_next_command(char **tokens, int *is_pipe)
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

int	pipeline_check_syntax(char **tokens)
{
	char	**next_command;
	int		is_pipe;
	
	while (*tokens)
	{
		next_command = get_next_command(tokens, &is_pipe);
		if (is_pipe && *++next_command == NULL)
		{
			ft_fprintf(2, NAME": syntax error `|'\n");
			return (-1); // syntax error
		}
		tokens = next_command;
	}
	return (0);
}

int	pipeline_control(char **tokens)
{
	char	**next_command;
	int		is_pipe;
	int		prev_is_pipe;
    int     fd;
	int		proc_pid;

	fd = 0;
	prev_is_pipe = 0;
	proc_pid = 0;
	while (*tokens)
	{
		next_command = get_next_command(tokens, &is_pipe);
		if (is_pipe)
			*next_command++ = NULL;
		proc_pid = command_execution(tokens, fd, &fd, is_pipe, prev_is_pipe);
		if (proc_pid == -1)
			break;
		prev_is_pipe = is_pipe;
		tokens = next_command;
	}
	return (wait_children(proc_pid));
}
