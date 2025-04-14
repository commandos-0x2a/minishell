/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:26:15 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/14 06:32:32 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_test(t_mini *mini, char **argv)
{
	extern char	**environ;
	char		*value;
	int			i;

	(void)argv;
	// ft_setenv("MY_VAR", "my_value", 1);
	value = ft_getenv(mini->env, "MY_VAR");
	ft_fprintf(2, "Current MY_VAR=%s\n", value);
	free(value);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "MY_VAR=", 7) == 0)
		{
			ft_fprintf(2, "Found in environ: %s\n", environ[i]);
			break ;
		}
		i++;
	}
	return (0);
}
