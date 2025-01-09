/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:12:35 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/08 12:42:33 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_redirection(char *token, int _dup)
{
	int	fd;
	char	*file;

	file = expand_str(token);
	if (!file)
		return (-1);
	if (ft_strcmp(file, "*") == 0)
	{
		ft_fprintf(2, NAME": %s: ambiguous redirect\n", token);
		free(file);
		return (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(NAME);
		free(file);
		return (-1);
	}
	free(file);
	if (_dup)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	out_append(char *token, int _dup)
{
	int fd;
	char	*file;


	file = expand_str(token);
	if (!file)
		return (-1);
	if (ft_strcmp(file, "*") == 0)
	{
		ft_fprintf(2, NAME": %s: ambiguous redirect\n", token);
		free(file);
		return (1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
		free(file);
		return (-1);
	}
	free(file);
	if (_dup)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	out_redirection(char *token, int _dup)
{
	int 	fd;
	char	*file;

	file = expand_str(token);
	if (!file)
		return (-1);
	if (ft_strcmp(file, "*") == 0)
	{
		ft_fprintf(2, NAME": %s: ambiguous redirect\n", token);
		free(file);
		return (1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		free(file);
		return (-1);
	}
	free(file);
	if (_dup)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}


void	swap_args(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**redirection_handler(char **tokens, int _dup)
{
	char	**argv;
	int		status;
	char	**last_argv;

	argv = NULL;
	status = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0)
		{
			*tokens = NULL;
			++tokens;
			*tokens = NULL;
		}
		else if (ft_strncmp(*tokens, "<<", 2) == 0)
		{
			*tokens = NULL;
		}
		else if (ft_strcmp(*tokens, "<") == 0)
		{
			*tokens = NULL;
			status = in_redirection(*++tokens, _dup);
			*tokens = NULL;
		}
		else if (ft_strncmp(*tokens, "<", 1) == 0)
		{
			status = in_redirection(*tokens + 1, _dup);
			*tokens = NULL;
		}
		else if (ft_strcmp(*tokens, ">>") == 0)
		{
			*tokens = NULL;
			status = out_append(*++tokens, _dup);
			*tokens = NULL;
		}
		else if (ft_strncmp(*tokens, ">>", 2) == 0)
		{
			status = out_append(*tokens + 2, _dup);
			*tokens = NULL;
		}
		else if (ft_strcmp(*tokens, ">") == 0)
		{
			*tokens = NULL;
			status = out_redirection(*++tokens, _dup);
			*tokens = NULL;
		}
		else if (ft_strncmp(*tokens, ">", 1) == 0)
		{
			status = out_redirection(*tokens + 1, _dup);
			*tokens = NULL;
		}
		else if (!argv)
		{
			argv = tokens;
			last_argv = tokens;
		}
		else
		{
			swap_args(++last_argv, tokens);
		}
		if (status != 0)
			return (NULL);

		tokens++;
	}
	if (!argv)
		return (tokens);
	return (argv);
}
