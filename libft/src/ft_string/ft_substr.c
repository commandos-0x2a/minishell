/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:27:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/28 00:05:06 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;
	size_t	r_len;

	s_len = ft_strlen(s);
	if (s_len == 0 || len == 0 || start >= s_len)
		return (ft_strdup(""));
	r_len = s_len - start;
	if (len < r_len)
		r_len = len;
	ret = malloc(++r_len);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, r_len);
	return (ret);
}
