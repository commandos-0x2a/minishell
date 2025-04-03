/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:57:21 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:45:23 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	len;
	unsigned int	i;
	char			*ret;

	len = ft_strlen(s);
	ret = malloc(++len);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	return (ret);
}

/**
Allowed functions : malloc
•Reproduce the behavior of the function strdup(man strdup).
•Here’s how it should be prototyped :
char *ft_strdup( char *src);
6

*/
