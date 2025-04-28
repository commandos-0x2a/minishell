/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:23:00 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/26 23:51:49 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(const char *file, int line)
{
	ft_fprintf(2, PREFIX"%s:%d: %s\n", file, line, strerror(errno));
	return (-1);
}

int	print_file_error(const char *file, int line, const char *target)
{
	ft_fprintf(2, PREFIX"%s:%d: %s: %s\n", file, line, target, strerror(errno));
	return (-1);
}
