/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:19:51 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 21:31:18 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_argv0(t_list *lst)
{
	
	while (lst && lst->str)
	{
		if (!ft_strcmp(lst->str, "<<") \
			|| !ft_strcmp(lst->str, ">>") \
			|| !ft_strcmp(lst->str, "<") \
			|| !ft_strcmp(lst->str, ">"))
			lst = lst->next;
		else
			return (lst->str);
		lst = lst->next;
	}
	return (NULL);
}
