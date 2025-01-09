/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:19:51 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/07 13:20:13 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*get_argv0(char **tokens)
{
	while (*tokens)
	{
		if (!ft_strcmp(*tokens, "<<") \
			|| !ft_strcmp(*tokens, ">>") \
			|| !ft_strcmp(*tokens, "<") \
			|| !ft_strcmp(*tokens, ">"))
			tokens++;
		else if (!ft_strncmp(*tokens, "<<", 2) \
				|| !ft_strncmp(*tokens, ">>", 2) \
				|| !ft_strncmp(*tokens, "<", 1) \
				|| !ft_strncmp(*tokens, ">", 1))
			;
		else
			return (*tokens);
		tokens++;
	}
	return (NULL);
}