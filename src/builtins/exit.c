/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:30:57 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/10 12:34:05 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void ft_free(char **argv)
{
	int i;

	i = 0;
	while(argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}


int	ft_exit(char **argv)
{
	int	status;

	ft_printf("exit\n");
	if (!argv[1])
	{
		// ft_free(argv);
		exit(0);
	}
	
	status = ft_atoi(argv[1]);
	if (argv[2])
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	else if (ft_str_is_numeric(argv[1]) == 0)
	{
		ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", argv[1]);
		// ft_free(argv);
		exit(255);
	}
	// ft_free(argv);
	exit(status);
}
