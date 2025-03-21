/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:05:57 by mkurkar           #+#    #+#             */
/*   Updated: 2025/03/21 12:39:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv)
{
	char	cwd[PATH_MAX_LEN];

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_fprintf(2, "minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}
