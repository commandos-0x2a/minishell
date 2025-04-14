/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:00:00 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/14 06:14:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lst_remove_one(t_list **lst, t_list *prev);

static void	remove_env_var(t_list **env, char *var_name)
{
	size_t	name_len;
	t_list	*cur;
	t_list	*prev;

	name_len = ft_strlen(var_name);
	cur = *env;
	prev = NULL;
	while (cur && cur->str)
	{
		if (ft_strncmp(cur->str, var_name, name_len) == 0 && \
			cur->str[name_len] == '=')
		{
			if (!prev)
				lst_remove_one(env, prev);
			else
				lst_remove_one(&cur, prev);
			return ;
		}
		cur = cur->next;
	}
}

int	ft_unset(t_mini *mini, char **argv)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			ft_fprintf(2, PREFIX"unset: not a valid identifier\n");
			return (1);
		}
		remove_env_var(&mini->env, argv[i]);
		i++;
	}
	return (0);
}
