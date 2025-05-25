/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:30:57 by mkurkar           #+#    #+#             */
/*   Updated: 2025/05/25 17:31:23 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	check_arg(char *s, int *status)
{
	char *ptr;

	ptr = s;
	if (ft_atoi_save_r(&ptr, status) == -1)
	{
		ft_fprintf(2, PREFIX"exit: %s: numeric argument required\n", s);
		*status = 2;
	}
	else if (ft_str_is_numeric(s) == 0)
	{
		ft_fprintf(2, PREFIX"exit: %s: numeric argument required\n", s);
		*status = 255;
	}
	return (0);
}

int	ft_exit(char **argv, int *_exit)
{
	int	status;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_printf("exit\n");
	if (!argv[1])
	{
		*_exit = 1;
		if (g_sig != 0)
			return (128 + g_sig);
		return (0);
	}
	check_arg(argv[1], &status);
	if (argv[2])
	{
		ft_fprintf(2, PREFIX"exit: too many arguments\n");
		return (1);
	}
	*_exit = 1;
	return (status);
}
