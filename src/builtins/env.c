/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:20:57 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/13 23:39:14 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_mini *mini, char **argv)
{
	t_list	*cur;

	if (argv && argv[1])
	{
		ft_fprintf(2, PREFIX"'%s': No such file or directory\n", argv[0]);
		return (127);
	}
	cur = mini->env;
	while (cur && cur->str)
	{
		ft_printf("%s\n", cur->str);
		cur = cur->next;
	}
	return (0);
}
