/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:12:35 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/07 13:53:22 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_ambiguous(char *token)
{
	char	*s;

	s = expand_str_no_quote(token);
	if (!s)
	{
		PRINT_ALLOCATE_ERROR;
		return (1);
	}
	while (*s)
	{
		if (*s == '*')
		{
			ft_fprintf(2, PREFIX"%s: ambiguous redirect\n", token);
			return (1);
		}
		if (*s == '\'' || *s == '"')
			s = ft_strchr(s + 1, *s);
		s++;
	}
	return (0);
}

static int	in_redirection(char *token, int change_std)
{
	int		fd;
	char	*filename;

	if (check_ambiguous(token))
		return (1);
	filename = expand_str(token);
	if (!filename)
	{
		PRINT_ALLOCATE_ERROR;
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		PRINT_FILE_ERROR(filename);
		free(filename);
		return (-1);
	}
	free(filename);
	if (change_std && dup2(fd, STDIN_FILENO))
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	out_append(char *token, int change_std)
{
	int		fd;
	char	*filename;

	if (check_ambiguous(token))
		return (1);
	filename = expand_str(token);
	if (!filename)
	{
		PRINT_ALLOCATE_ERROR;
		return (-1);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		PRINT_FILE_ERROR(filename);
		free(filename);
		return (-1);
	}
	free(filename);
	if (change_std && dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	out_redirection(char *token, int change_std)
{
	int		fd;
	char	*filename;

	if (check_ambiguous(token))
		return (1);
	filename = expand_str(token);
	if (!filename)
	{
		PRINT_ALLOCATE_ERROR;
		return (-1);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		PRINT_FILE_ERROR(filename);
		free(filename);
		return (-1);
	}
	free(filename);
	if (change_std && dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/*
static int	heredoc_redirection(char *token, int change_std)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	heredoc_start_read(token, pipefd[1]);
	close(pipefd[1]);
	if (change_std && dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}
*/

int	redirection_handler(char **tokens, int heredoc_fd, int change_std)
{
	int		status;

	status = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0)
		{
			++tokens;
			if (heredoc_fd > 0 && change_std)
				status = dup2(heredoc_fd, STDIN_FILENO);
		}
		else if (ft_strcmp(*tokens, "<") == 0)
			status = in_redirection(*++tokens, change_std);
		else if (ft_strcmp(*tokens, ">>") == 0)
			status = out_append(*++tokens, change_std);
		else if (ft_strcmp(*tokens, ">") == 0)
			status = out_redirection(*++tokens, change_std);
		if (status != 0)
			return (status);
		tokens++;
	}
	return (0);
}
