/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:32:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 06:42:04 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lst_remove_one(t_list **lst, t_list *prev)
{
	t_list	*cur;

	if (!*lst)
		return ;

	cur = *lst;
	if (prev)
		prev->next = cur->next;
	*lst = cur->next;
	if (cur->str)
		free(cur->str);
	free(cur);
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
		if (ft_strcmp(cur->str, "<<") == 0 \
			|| ft_strcmp(cur->str, "<") == 0 \
			|| ft_strcmp(cur->str, ">>") == 0 \
			|| ft_strcmp(cur->str, ">") == 0)
		{
			lst_remove_one(&cur, prev);
			lst_remove_one(&cur, prev);
			continue;
		}
		if (!prev)
			start = cur;
		prev = cur;
		cur = cur->next;
	}
	*lst = start;
}

char	**lst_2_argv(t_list **lst)
{
	char	**argv;
	t_list	*current;
	static int	i;
	int			_i;

	_i = i++;
	if (!*lst || !(*lst)->str)
	{
		lst_clean(lst);
		i = 0;
		return (ft_calloc(_i + 1, sizeof(char *)));
	}
	current = *lst;
	*lst = (*lst)->next;
	argv = lst_2_argv(lst);
	if (!argv)
		free(current->str);
	else
		argv[_i] = current->str;
	free(current);
	return (argv);
}
