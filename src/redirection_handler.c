/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:12:35 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/07 08:12:59 by yaltayeh         ###   ########.fr       */
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

char	**redirection_handler(char **tokens, int *status)
{
	char	**new_tokens;

	new_tokens = NULL;
	*status = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0)
		{
			*tokens = NULL;
			*status = here_doc(*(++tokens));
		}
		else if (ft_strncmp(*tokens, "<<", 2) == 0)
		{
			*status = here_doc(*tokens + 2);
			*tokens = NULL;
		}
		else if (ft_strcmp(*tokens, "<") == 0)
		{
			*tokens = NULL;
			*status = in_redirection(*++tokens);
		}
		else if (ft_strncmp(*tokens, "<", 1) == 0)
		{
			*status = in_redirection(*tokens + 1);
			*tokens = NULL;
		}
		else if (ft_strcmp(*tokens, ">>") == 0)
		{
			*tokens = NULL;
			*status = out_append(*++tokens);
		}
		else if (ft_strncmp(*tokens, ">>", 2) == 0)
		{
			*status = out_append(*tokens + 2);
			*tokens = NULL;
		}
		else if (ft_strcmp(*tokens, ">") == 0)
		{
			*tokens = NULL;
			*status = out_redirection(*++tokens);
		}
		else if (ft_strncmp(*tokens, ">", 1) == 0)
		{
			*status = out_redirection(*tokens + 1);
			*tokens = NULL;
		}
		else if (!new_tokens)
			new_tokens = tokens;

		if (*status != 0)
			return (NULL);

		tokens++;
	}
	return (new_tokens);
}
