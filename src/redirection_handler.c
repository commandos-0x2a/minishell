/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:12:35 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 21:36:03 by yaltayeh         ###   ########.fr       */
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

int	redirection_handler(t_list *lst, int heredoc_fd, int change_std)
{
	int		status;
	
	status = 0;
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "<<") == 0)
		{
			if (heredoc_fd > 0 && change_std)
				status = dup2(heredoc_fd, STDIN_FILENO);
		}
		else if (ft_strcmp(lst->str, "<") == 0)
			status = in_redirection(lst->next->str, change_std);
		else if (ft_strcmp(lst->str, ">>") == 0)
			status = out_append(lst->next->str, change_std);
		else if (ft_strcmp(lst->str, ">") == 0)
			status = out_redirection(lst->next->str, change_std);
		else
		{
			lst = lst->next;
			continue ;
		}
		if (status != 0)
			return (status);
		lst = lst->next->next;
	}
	return (0);
}
