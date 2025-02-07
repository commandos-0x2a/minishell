/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:00:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/07 19:45:02 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int ft_free_array_str(char **ptr)
{
	char **current;

	if (!ptr)
		return (-1);
	current = ptr;
	while (*current)
		free(*current++);
	free(ptr);
	return (-1);
}
