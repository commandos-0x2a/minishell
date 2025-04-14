/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_with_recursive.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:41:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 22:44:20 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void iter_func(int count)
{
	static int	i;
	int			_i;

	_i = i++;
	if (count == 0)
	{
		i = 0;
		return ;
	}
	iter_func(count - 1);
	printf("i: %d\n", _i);
}

int main()
{
	iter_func(5);
	iter_func(6);
	return (0);
}