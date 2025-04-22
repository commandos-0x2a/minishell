/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:32:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/22 15:13:02 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_2_argv(t_list **lst, int flcean)
{
	char		**argv;
	t_list		*current;
	static int	i;
	int			_i;

	_i = i++;
	if (!*lst || !(*lst)->str)
	{
		if (flcean)
			lst_clean(lst);
		i = 0;
		return (ft_calloc(_i + 1, sizeof(char *)));
	}
	current = *lst;
	*lst = (*lst)->next;
	argv = lst_2_argv(lst, flcean);
	if (!argv)
		free(current->str);
	else
		argv[_i] = current->str;
	free(current);
	return (argv);
}

char	*get_argv0(t_list *lst)
{
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "<<") == 0
			|| ft_strcmp(lst->str, ">>") == 0
			|| ft_strcmp(lst->str, "<") == 0
			|| ft_strcmp(lst->str, ">") == 0)
			lst = lst->next;
		else
			return (lst->str);
		lst = lst->next;
	}
	return (NULL);
}

void	get_argv(t_list **lst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*start;

	cur = *lst;
	prev = NULL;
	start = NULL;
	while (cur && cur->str)
	{
		if (ft_strcmp(cur->str, "<<") == 0
			|| ft_strcmp(cur->str, "<") == 0
			|| ft_strcmp(cur->str, ">>") == 0
			|| ft_strcmp(cur->str, ">") == 0)
		{
			lst_remove_one(&cur, prev);
			lst_remove_one(&cur, prev);
			continue ;
		}
		if (!prev)
			start = cur;
		prev = cur;
		cur = cur->next;
	}
	*lst = start;
}
