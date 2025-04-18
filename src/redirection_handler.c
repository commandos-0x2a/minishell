/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:12:35 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 15:43:09 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ambiguous(t_mini *mini, char **filename_r)
{
	t_list	*lst;

	lst = ft_calloc(1, sizeof(*lst));
	if (!lst)
	{
		PRINT_ALLOCATE_ERROR;
		return (-1);
	}
	lst->str = ft_strdup(*filename_r);
	if (!lst->str)
	{
		lst_clean(&lst);
		return (-1);
	}
	if (expand_tokens(mini, lst) != 0)
	{
		lst_clean(&lst);
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

static int	in_redirection(t_mini *mini, char *token, int change_std)
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
	if (change_std && dup2(fd, STDIN_FILENO))
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	out_append(t_mini *mini, char *token, int change_std)
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
	if (change_std && dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	out_redirection(t_mini *mini, char *token, int change_std)
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
	if (change_std && dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirection_handler(t_mini *mini, int heredoc_fd, int change_std)
{
	int		status;
	t_list	*lst;
	
	lst = mini->tokens;
	status = 0;
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "<<") == 0)
		{
			if (heredoc_fd > 0 && change_std)
				status = dup2(heredoc_fd, STDIN_FILENO);
		}
		else if (ft_strcmp(lst->str, "<") == 0)
			status = in_redirection(mini, lst->next->str, change_std);
		else if (ft_strcmp(lst->str, ">>") == 0)
			status = out_append(mini, lst->next->str, change_std);
		else if (ft_strcmp(lst->str, ">") == 0)
			status = out_redirection(mini, lst->next->str, change_std);
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
