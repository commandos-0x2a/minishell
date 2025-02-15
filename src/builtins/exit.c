/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:30:57 by mkurkar           #+#    #+#             */
/*   Updated: 2025/02/15 22:49:35 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **argv, int *_exit)
{
	int	status;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_printf("exit\n");
	if (!argv[1])
	{
		*_exit = 1;
		return (0);
	}
	status = ft_atoi(argv[1]);
	if (argv[2])
	{
		ft_fprintf(2, NAME": exit: too many arguments\n");
		return (1);
	}
	else if (ft_str_is_numeric(argv[1]) == 0)
	{
		ft_fprintf(2, NAME": exit: %s: numeric argument required\n", argv[1]);
		status = 255;
	}
	*_exit = 1;
	return (status);
}
