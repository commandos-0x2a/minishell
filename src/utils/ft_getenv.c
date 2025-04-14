/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 07:25:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 22:58:16 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(t_list *env, const char *name)
{
	size_t	name_len;

	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	while (env && env->str)
	{
		if (ft_strncmp(env->str, name, name_len) == 0 && \
				env->str[name_len] == '=')
			return (ft_strdup(env->str + name_len + 1));
		env = env->next;
	}
	return (NULL);
}

t_list	*copy_env_variables(void)
{
	t_list				*lst;
	extern const char	**environ;
	static int			i;
	int					_i;

	_i = i++;
	if (!environ[_i])
	{
		i = 0;
		return (ft_calloc(1, sizeof(t_list)));
	}
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->str = ft_strdup(environ[_i]);
	if (!lst->str)
	{
		free(lst);
		return (NULL);
	}
	lst->next = copy_env_variables();
	if (!lst->next)
	{
		free(lst->str);
		free(lst);
		return (NULL);
	}
	return (lst);
}
