/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:33:34 by mkurkar           #+#    #+#             */
/*   Updated: 2025/06/04 21:14:36 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	put_char_to_buf(char *buf, char c, size_t *pos, size_t size)
{
	if (buf && size > 0 && *pos < size - 1)
		buf[*pos] = c;
	if (c)
		++*pos;
	if (buf && size > 0 && *pos == size - 1)
		buf[*pos] = '\0';
}

static void	ft_handle_number(int n, char *buf, size_t *pos, size_t size)
{
	long	num;
	int		i;
	char	digits[12];

	i = 0;
	num = n;
	if (num < 0)
	{
		put_char_to_buf(buf, '-', pos, size);
		num = -num;
	}
	if (num == 0)
	{
		put_char_to_buf(buf, '0', pos, size);
		return ;
	}
	while (num > 0)
	{
		digits[i++] = '0' + (num % 10);
		num /= 10;
	}
	while (i > 0)
		put_char_to_buf(buf, digits[--i], pos, size);
}

static void	ft_handle_string(const char *src, char *buf,
					size_t *pos, size_t size)
{
	while (src && *src)
		put_char_to_buf(buf, *src++, pos, size);
}

int	ft_vsnprintf(char *buf, size_t size, const char *format, va_list ap)
{
	size_t	pos;

	if (!format)
		return (0);
	pos = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd')
				ft_handle_number(va_arg(ap, int), buf, &pos, size);
			else if (*format == 's')
				ft_handle_string(va_arg(ap, char *), buf, &pos, size);
			format++;
		}
		else
			put_char_to_buf(buf, *format++, &pos, size);
	}
	put_char_to_buf(buf, '\0', &pos, size);
	return ((int)pos);
}
