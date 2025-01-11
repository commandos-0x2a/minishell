/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:00:00 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/11 16:37:08 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_env_var(char *var)
{
	char ***g_env_copy = __init__env();
	int i, j;
	int len;

	if (!(*g_env_copy))
		return;

	len = ft_strlen(var);
	i = 0;
	while ((*g_env_copy)[i])
	{
		if (ft_strncmp((*g_env_copy)[i], var, len) == 0 &&
			((*g_env_copy)[i][len] == '=' || (*g_env_copy)[i][len] == '\0'))
		{
			free((*g_env_copy)[i]);
			j = i;
			while ((*g_env_copy)[j])
			{
				(*g_env_copy)[j] = (*g_env_copy)[j + 1];
				j++;
			}
			return;
		}
		i++;
	}
}

int ft_unset(char **argv)
{
	int i;

	if (!argv[1])
		return (0);

	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			ft_putendl_fd("minishell: unset: not a valid identifier", 2);
			return (1);
		}
		remove_env_var(argv[i]);
		i++;
	}
	return (0);
}
