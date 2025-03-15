/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expander2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:31:07 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/17 14:34:38 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	old_size;

	old_size = *(((size_t *)ptr) - 1);
}


char	*expand_str_env_variable(char *str)
{
	char	*result;
	char	*temp;
	char	quote_char;
	int		i;


	result = ft_strdup("");
	while (*str)
	{
		if (!result) // to detect all result malloc failed
			return (NULL);
		if (*str == '\'')
		{
			str = ft_strchr(str + 1, '\'');
			str++;
			continue ;
		}
		if (*str == '\"')
		{
			while (*str && *str != '\"')
			{
				if (*str == '$')
				{
					temp = expand_env_var(str, &i);
					if (temp)
						result = join_and_free(result, temp);
					continue;
				}
				str++;
			}
		}
		// Handle environment variables
		if (*str == '$' && quote_char != '\'')
		{
			temp = expand_env_var(str, &i);
			if (temp)
				result = join_and_free(result, temp);
			continue;
		}
		// Normal character
		temp = ft_substr(str, i, 1);
		result = join_and_free(result, temp);
	}
	return (result);
}
