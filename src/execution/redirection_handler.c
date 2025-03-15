/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:12:35 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/15 21:40:38 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_ambiguous(char *token)
{
	char	*s;

	s = expand_str_no_quote(token);
	if (!s)
	{
		ft_fprintf(2, PREFIX"check_ambiguous: %s\n", strerror(errno));
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
	char	*file;

	if (check_ambiguous(token))
		return (1);
	file = expand_str(token);
	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, PREFIX"%s: %s\n", file, strerror(errno));
		free(file);
		return (-1);
	}
	free(file);
	if (change_std)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	out_append(char *token, int change_std)
{
	int		fd;
	char	*file;

	if (check_ambiguous(token))
		return (1);
	file = expand_str(token);
	if (!file)
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_fprintf(2, PREFIX"%s\n", strerror(errno));
		free(file);
		return (-1);
	}
	free(file);
	if (change_std)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	out_redirection(char *token, int change_std)
{
	int		fd;
	char	*file;

	if (check_ambiguous(token))
		return (1);
	file = expand_str(token);
	if (!file)
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_fprintf(2, PREFIX"%s\n", strerror(errno));
		free(file);
		return (-1);
	}
	free(file);
	if (change_std)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirection_handler(char **tokens, int here_doc_fd, int change_std)
{
	int		status;

	status = 0;

	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0)
		{
			++tokens;
			if (change_std && here_doc_fd > -1)
				status = dup2(here_doc_fd, STDIN_FILENO);
		}
		else if (ft_strcmp(*tokens, "<") == 0)
			status = in_redirection(*++tokens, change_std);
		else if (ft_strcmp(*tokens, ">>") == 0)
			status = out_append(*++tokens, change_std);
		else if (ft_strcmp(*tokens, ">") == 0)
			status = out_redirection(*++tokens, change_std);
		if (status != 0)
		{
			if (here_doc_fd > -1)
				close(here_doc_fd);
			return (status);
		}
		tokens++;
	}
	if (here_doc_fd > -1)
		close(here_doc_fd);
	return (0);
}
