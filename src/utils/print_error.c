/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:23:00 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/30 09:12:05 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef DEBUG

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

#else

int	print_error(const char *file, int line)
{
	(void)file;
	(void)line;
	ft_fprintf(2, PREFIX"%s\n", strerror(errno));
	return (-1);
}

int	print_file_error(const char *file, int line, const char *target)
{
	(void)file;
	(void)line;
	ft_fprintf(2, PREFIX"%s: %s\n", target, strerror(errno));
	return (-1);
}

#endif
