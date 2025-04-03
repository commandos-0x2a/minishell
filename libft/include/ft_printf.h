/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:02:23 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/15 15:47:12 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define CONVENTIONS_CHARACTERS "cspdiuxX%"
# define FLAGS_CHARACTERS "0-.#+ 123456789"
# define HEX_BASE "0123456789abcdef"
# define HEX_BASE_UPPER "0123456789ABCDEF"
# define DECIMAL_BASE "0123456789"

typedef enum e_flags
{
	NONE = 0,
	ZERO = 1 << 0,
	MINUS = 1 << 1,
	DOT = 1 << 2,
	SHARP = 1 << 3,
	PLUS = 1 << 4,
	SPACE = 1 << 5,
	NUMBER = 1 << 6,
}	t_flags;

typedef struct s_printf_data
{
	t_flags		flags;
	va_list		*ap;
	size_t		numbers[2];
	int			fd;
}	t_printf_data;

int		ft_vprintf(const char *fmt, va_list	*ap);

int		ft_printf(const char *fmt, ...) \
		__attribute__((format(printf, 1, 2)));

int		ft_fprintf(int fd, const char *fmt, ...) \
		__attribute__((format(printf, 2, 3)));

int		ft_vfprintf(int fd, const char *fmt, va_list *ap);

int		ft_snprintf(char *str, size_t size, const char *format, ...) \
		__attribute__((format(printf, 3, 4)));

t_flags	ft_flags_parser(const char **fmt, size_t *numbers, t_flags flags);

int		ft_printf_redirect(char conversions, t_printf_data data);

size_t	ft_sharp_apply(int upper, int fd);
size_t	ft_zero_apply(size_t num, size_t count, int fd);
size_t	ft_blank_apply(size_t num, size_t count, int fd);

size_t	ft_char_handle(t_printf_data data);
size_t	ft_str_handle(t_printf_data data);
size_t	ft_pointer_handle(t_printf_data data);
size_t	ft_decimal_handle(t_printf_data data);
size_t	ft_u_decimal_handle(t_printf_data data);
size_t	ft_hex_handle(t_printf_data data, int upper);
size_t	ft_percent_handle(t_printf_data data);

#endif