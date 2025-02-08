/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:32:23 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/08 17:34:17 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens *tok)
{
	int	i;

	i = 0;
	if (tok->tokens)
	{
		while (i < tok->nb_tokens)
		{
			if (tok->tokens[i])
				free(tok->tokens[i]);
			tok->tokens[i] = NULL;
			i++;
		}
		free(tok->tokens);
		tok->tokens = NULL;
	}
	tok->nb_tokens = 0;
}