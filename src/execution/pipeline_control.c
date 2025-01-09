/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/09 22:02:01 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_next_pipeline(char **tokens, int *is_pipe)
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

int	pipeline_control(char **tokens)
{
	char	**next_pipeline;
	int		is_pipe;
	int		prev_is_pipe;
    int     fd;
	int		proc_pid;

	fd = 0;
	prev_is_pipe = 0;
	proc_pid = -1;
	while (*tokens)
	{
		next_pipeline = get_next_pipeline(tokens, &is_pipe);

		*next_pipeline = NULL;

		if (is_pipe && *++next_pipeline == NULL)
		{
			ft_fprintf(2, NAME": syntax error `|'\n");
			return (-1); // syntax error
		}
		proc_pid = command_execution(tokens, fd, &fd, is_pipe, prev_is_pipe);
		if (proc_pid == -1)
			break;
		
		prev_is_pipe = is_pipe;
		tokens = next_pipeline;
	}
	return (wait_children(proc_pid));
}
