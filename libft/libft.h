/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:34:48 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/13 02:38:33 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

void				*ft_memset(void *ptr, int x, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *to, const void *from, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_calloc(size_t count, size_t size);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strchr(const char *str, int search_str);
char				*ft_strrchr(const char *str, int chr);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char				*get_next_line(int fd);
size_t				ft_strlen_gnl(const char *str);
char				*ft_strdup_gnl(const char *s1);
char				*ft_strjoin_gnl(char *s1, const char *s2);
char				*ft_substr_gnl(char const *s, unsigned int start,
						size_t len);
char				*ft_strchr_gnl(char *str, char search_str);
#endif
