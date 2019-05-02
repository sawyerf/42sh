/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 22:23:00 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/16 15:20:17 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <inttypes.h>
# include <string.h>
# include <unistd.h>
# include "ft_printf.h"
# include "get_next_line.h"

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

extern int			g_optind;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack,
											const char *needle, size_t len);
int					ft_isalldigit(char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_strnsplit(char const *s, char *sep);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst);
void				ft_lstdel(t_list **alst);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_getopt(char **argv, char *opstring);
char				**ft_splitblanks(char const *s);
int					ft_isblank(char c);
char				*ft_strlower(char *s);
char				*ft_strndup(const char *s, int len);
void				ft_strrev(char *str);
int					ft_utoa_base(uintmax_t nbr, int base, char *str, int rev);
int					ft_inner_itoa(intmax_t nbr, int base, char *str);
int					ft_itoa_base(intmax_t nbr, int base, char *str, int rev);
void				ft_swap_char(char *a, char *b);
int					ft_printf(const char *s, ...);
int					ft_dprintf(int fd, const char *format, ...);
char				*ft_zprintf(const char *format, ...);
int					ft_cisin(char *s, char c);
char				*ft_strechr(const char *s, int c);
void				ft_tabdel(char ***tab);
char				**ft_tabdup(char **tab);
int					ft_tablen(char **tab);
char				**ft_tabnew(size_t len);
char				**ft_tabcpy(char **tab);
char				**ms_tabcpy(char **dst, char **cpy);
int					ft_strichr(char *s, char c, int n);
int					ft_strisprint(char *str);
int					ft_strisdigit(char *str);
int					ft_strnext(char *str, char *to);
char				*ft_replace(char *str, char *to, char *by);
char				*ft_rereplace(char *str, char *to, char *by);
int					ft_rperr(int ret, char *str);
int					ft_tabcmp(char **tab, char *s);

#endif
