/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:59:57 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/08 01:32:26 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*fclean_list(t_list **lst)
{
	t_list	*next;

	while (*lst)
	{
		free((*lst)->token);
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	return (NULL);
}

void	*clean_list(t_list **lst)
{
	t_list	*next;

	while (*lst && (*lst)->token)
	{
		free((*lst)->token);
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	if (*lst)
	{
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	return (*lst);
}

