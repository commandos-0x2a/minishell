/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:19:51 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 02:05:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_argv0(t_tokens *lst)
{
	
	while (lst && lst->token)
	{
		if (!ft_strcmp(lst->token, "<<") \
			|| !ft_strcmp(lst->token, ">>") \
			|| !ft_strcmp(lst->token, "<") \
			|| !ft_strcmp(lst->token, ">"))
			lst = lst->next;
		else
			return (lst->token);
		lst = lst->next;
	}
	return (NULL);
}
