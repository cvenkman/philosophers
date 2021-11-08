/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:43:54 by cvenkman          #+#    #+#             */
/*   Updated: 2021/09/19 18:58:21 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
#include <errno.h>

void	putstr_exit(char *str);
void	perror_exit(char *str);
void	perror_return(char *str);
void	ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *str, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strncmp(char const *s1, char const *s2, size_t n);
int		ft_isprint(int sym);
int		ft_isalpha(int sym);
int		ft_isdigit(int sym);
int		ft_isalnum(int sym);
int		ft_isascii(int sym);
int		ft_toupper(int sym);
int		ft_tolower(int sym);
int		error_return(char *str);
int		ft_atoi(char const *str);
int		perror_return_number(char *str, int num);
int		ft_strcmp(char const *str1, char const *str2);
void	*error_return_void(char *str);
void	*ft_calloc(size_t n, size_t size);
char	*ft_itoa(int n);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int sym);
char	*ft_strrchr(const char *str, int sym);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(char const *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
