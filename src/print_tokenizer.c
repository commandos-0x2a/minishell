/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:00:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 02:05:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str_no_quote(char *str);

void	print_tokenizer(t_tokens **lst, int indent)
{
	int i;
	t_tokens	*cur;

	get_argv(lst);
	i = 0;
	cur = *lst;
	while (lst && cur->token)
	{
		printf("%-*s%i: %s\n", indent, "", i, cur->token);
		cur = cur->next;
		i++;
	}
}
