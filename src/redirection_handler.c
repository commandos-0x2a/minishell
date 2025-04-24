/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:12:35 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/24 13:41:33 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ambiguous(t_mini *mini, char **filename_r)
{
	t_list	*lst;

	lst = expand_tokens_2lst(mini, *filename_r);
	if (!lst)
	{
		PRINT_ALLOCATE_ERROR;
		return (-1);
	}
	if (!lst->str || (lst->next && lst->next->str))
	{
		lst_clean(&lst);
		ft_fprintf(2, PREFIX"%s: ambiguous redirect\n", *filename_r);
		return (1);
	}
	*filename_r = lst->str;
	lst->str = NULL;
	lst_clean(&lst);
	return (0);
}

static int	in_redirection(t_mini *mini, char *token)
{
	int		fd;
	char	*filename;

	filename = token;
	if (is_ambiguous(mini, &filename) != 0)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		PRINT_FILE_ERROR(filename);
		free(filename);
		return (-1);
	}
	free(filename);
	if (dup2(fd, STDIN_FILENO))
	{
		PRINT_SYSCALL_ERROR;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	out_append(t_mini *mini, char *token)
{
	int		fd;
	char	*filename;

	filename = token;
	if (is_ambiguous(mini, &filename) != 0)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		PRINT_FILE_ERROR(filename);
		free(filename);
		return (-1);
	}
	free(filename);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		PRINT_SYSCALL_ERROR;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	out_redirection(t_mini *mini, char *token)
{
	int		fd;
	char	*filename;

	filename = token;
	if (is_ambiguous(mini, &filename) != 0)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		PRINT_FILE_ERROR(filename);
		free(filename);
		return (-1);
	}
	free(filename);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		PRINT_SYSCALL_ERROR;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirection_handler(t_mini *mini, int heredoc_fd)
{
	int		err;
	t_list	*lst;

	err = 0;
	lst = mini->tokens;
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "<<") == 0)
			err = dup2(heredoc_fd, STDIN_FILENO);
		else if (ft_strcmp(lst->str, "<") == 0)
			err = in_redirection(mini, lst->next->str);
		else if (ft_strcmp(lst->str, ">>") == 0)
			err = out_append(mini, lst->next->str);
		else if (ft_strcmp(lst->str, ">") == 0)
			err = out_redirection(mini, lst->next->str);
		else
		{
			lst = lst->next;
			continue ;
		}
		if (err != 0)
			return (err);
		lst = lst->next->next;
	}
	return (0);
}
