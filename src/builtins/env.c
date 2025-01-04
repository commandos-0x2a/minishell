/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:20:57 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/04 21:18:34 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **argv)
{
	extern char	**environ;
	int			i;

	if (argv && argv[1])
	{
		ft_fprintf(2, "env: '%s': No such file or directory\n", argv[1]);
		return (127);
	}

	i = 0;
	while (environ[i])
	{
		ft_printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
