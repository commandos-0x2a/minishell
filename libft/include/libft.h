/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:15:57 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/25 17:30:07 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);

size_t	ft_strlen(const char *s);

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

int		ft_atoi(const char *nptr);
int		ft_atoi_r(const char **p_nptr);
int		ft_atoi_save_r(char **p_nptr, int *res);
size_t	ft_atou(const char *nptr);
size_t	ft_atou_r(const char **p_nptr);

int		ft_strcmp(const char *s1, const char *s2n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(int count, ...);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n, int with_sign);
char	*ft_itoa_base(unsigned long n, char *base_sym);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

int		ft_putchar(char c);
int		ft_putstr(const char *s);
int		ft_putnbr_with_zero(int n, int zero_count);
int		ft_puthexadecimal(unsigned int x, int is_lower);
int		ft_putbase_fd(unsigned long n, char *base_symbol, int fd);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);

char	*ft_strtok(char *s, const char *d);
int		ft_str_is_numeric(const char *str);

#endif
