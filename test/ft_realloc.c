/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:34:52 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/17 15:04:25 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	old_size;

	old_size = (*(((size_t *)ptr) - 1) / sizeof(size_t)) * sizeof(size_t) - sizeof(size_t);
    printf("old_size: %zu\n - usable_size %zu\n", old_size, malloc_usable_size(ptr));
    // void *new_data = malloc(size);
    // memmove(new_data, ptr,  malloc_usable_size(ptr));
    // free(ptr);
    // return new_data;
}

int main()
{
    void *ptr = malloc(100);
    ptr = ft_realloc(ptr, 200);
    // free(ptr);
}