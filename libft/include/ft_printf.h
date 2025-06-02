/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:02:23 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/06/02 22:31:49 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_vprintf(const char *fmt, va_list	ap);

int		ft_vsnprintf(char *buf, size_t size, const char *format, va_list ap);

int		ft_printf(const char *fmt, ...)
		__attribute__((format(printf, 1, 2)));

int		ft_fprintf(int fd, const char *fmt, ...)
		__attribute__((format(printf, 2, 3)));

int		ft_vfprintf(int fd, const char *fmt, va_list ap);

int		ft_snprintf(char *str, size_t size, const char *format, ...)
		__attribute__((format(printf, 3, 4)));

#endif