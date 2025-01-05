/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:26:15 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/05 17:33:16 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_test(char **argv)
{
	(void)argv;
	ft_setenv("MY_VAR", "my_value", 1);
	ft_fprintf(2, "MY_VAR=%s\n", ft_getenv("MY_VAR"));
	ft_putenv("MY_VAR=ThisIsGood");
	ft_fprintf(2, "MY_VAR=%s\n", ft_getenv("MY_VAR"));
	return (0);
}
