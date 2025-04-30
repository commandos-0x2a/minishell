/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:05:57 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/19 12:16:57 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv)
{
	char	cwd[PATH_MAX];

	if (argv[0] && argv[1])
	{
		ft_fprintf(2, "pwd: too many arguments\n");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_fprintf(2, "minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}
