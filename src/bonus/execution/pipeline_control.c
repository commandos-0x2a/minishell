/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/21 15:23:22 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static char	**get_next_command(char **tokens, int *is_pipe)
{
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "|") == 0)
		{
			*is_pipe <<= 1;
			*is_pipe |= 1;
			return (tokens);
		}
		tokens++;
	}
	*is_pipe <<= 1;
	return (tokens);
}
*/

static char	**get_next_command(char **tokens, int *is_pipe)
{
	char	**next;

	next = ft_tokpbrk(tokens, "|", NULL);
	*is_pipe <<= 1;
	if (*next)
		*is_pipe |= 1;
	return (next);
}

int	pipeline_check_syntax(char **tokens, char **tokens_brk)
{
	char	**next_command;
	int		is_pipe;

	is_pipe = 0;
	while (*tokens && tokens < tokens_brk)
	{
		next_command = get_next_command(tokens, &is_pipe);
		if ((is_pipe & IS_PIPE) && *++next_command == NULL)
		{
			ft_fprintf(2, PREFIX"syntax error `|'\n");
			return (-1);
		}
		// while (*tokens && tokens != next_command)
		// {
		// 	if (ft_strcmp(*tokens, "<<") == 0 \
		// 		|| ft_strcmp(*tokens, "<") == 0 \
		// 		|| ft_strcmp(*tokens, ">>") == 0 \
		// 		|| ft_strcmp(*tokens, ">") == 0)
		// 			tokens++;
		// 	if (tokens == next_command)
		// 	{
		// 		ft_fprintf(2, PREFIX"syntax error op `|'\n");
		// 		return (-1);	
		// 	}
		// 	tokens++;
		// }
		// if (is_pipe & IS_PIPE)
		// 	tokens++;
		tokens = next_command;
	}
	return (0);
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

int	pipeline_control(t_tokens *tok, char **pipeline)
{
	int		is_pipe;
	int		fd;
	char	**next_command;
	int		i;

	tok->nb_command = get_nb_command(tok->tokens);
	tok->children_pid = ft_calloc(tok->nb_command, sizeof(pid_t));
	if (!tok->children_pid)
		return (-1);
	fd = -1;
	is_pipe = 0;
	i = 0;
	while (*pipeline)
	{
		next_command = get_next_command(pipeline, &is_pipe);
		if (is_pipe & IS_PIPE)
		{
			free(*next_command);
			*next_command++ = NULL;
		}
		tok->children_pid[i] = command_execution(tok, pipeline, &fd, is_pipe);
		if (tok->children_pid[i] == -1)
			break ;
		if (waitpid(tok->children_pid[i], NULL, WUNTRACED) == -1)
			break ;
		pipeline = next_command;
		i++;
	}
	while (i--)
	{
		kill(tok->children_pid[i], SIGCONT);
		waitpid(tok->children_pid[i], NULL, WCONTINUED);
		// i++;
	}
	return (wait_children(tok->children_pid[i - 1]));
}
