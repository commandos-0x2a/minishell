/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:02:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 06:18:38 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include <stdlib.h>

#define PREFIX "minishell: "


# define PRINT_ERRNO \
	ft_fprintf(2, PREFIX"%s:%d: %s\n", __FILE__, __LINE__, strerror(errno))
	
# define PRINT_ALLOCATE_ERROR \
	ft_fprintf(2, PREFIX"%s:%d: %s\n", __FILE__, __LINE__, strerror(errno))
	
	# define PRINT_FILE_ERROR(filename) \
	ft_fprintf(2, PREFIX"%s:%d: %s %s\n", __FILE__, __LINE__, filename, strerror(errno))
	
# define PRINT_SYSCALL_ERROR \
	ft_fprintf(2, PREFIX"%s:%d: %s\n", __FILE__, __LINE__, strerror(errno))


// libft function
size_t	ft_join_path(char *dest, const char *path1, const char *path2);
int		ft_setenv(const char *name, const char *value, int overwrite);
int		ft_free_array_str(char **ptr);
char	**ft_tokpbrk(char **tokens, const char *strset, ...);
char	**ft_split(const char *s, char *d);

char	**copy_dptr(char **dptr);
void	free_dptr(char **ptr);

#endif