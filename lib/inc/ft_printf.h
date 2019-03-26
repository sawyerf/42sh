/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glavigno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:44:50 by glavigno          #+#    #+#             */
/*   Updated: 2019/03/26 15:05:07 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <inttypes.h>

typedef struct		s_base
{
	char			type;
	int				base;
}					t_base;

typedef struct		s_opt
{
	char			*tmp;
	char			sign[2];
	int				nb_sig;
	int				nb_zero;
	int				nb_p;
	int				nb_sp;
	int				nb_0;
	int				size;
	int				nb_spe;
}					t_opt;

typedef struct		s_printf
{
	int				needconv;
	int				len;
	char			*var;
	char			settings[5];
	char			type;
	int				pre[3];
	char			size[2];
	t_opt			opt;
	struct s_printf	*next;
}					t_printf;

t_printf			*pf_parser(const char *str);
t_printf			*ft_pushback(t_printf *lst, t_printf *add);
t_printf			*pf_prnew(char *str, int needconv);
t_opt				pf_optnew(void);
t_opt				pf_len(t_printf *lst, t_opt opt);
t_opt				pf_lenu(t_printf *lst, t_opt opt);
t_opt				pf_len_f(t_printf *lst, t_opt opt);
int					lenall(t_printf *lst);
int					ft_cisin(char *s, char c);
int					ft_printf(const char *format, ...);
int					pf_base(char c);
char				*utoa_base(t_printf *lst, unsigned long long n, int b);
char				*stoa_base(t_printf *lst, long long n, int b);
char				*pf_options(char *s, t_opt opt);
char				*pf_putstr(t_printf *lst, const char *s);
char				*pf_putaddr(t_printf *lst, void *addr);
char				*pf_putchar(t_printf *lst, char c);
char				*pf_addsp(char *s, int n);
char				*pf_ftoa(t_printf *lst, double n);
char				*pf_ftoa_exep(t_printf *lst, double n);
void				pf_prdel(t_printf *lst);
void				pf_replace(char *s, char c1, char c2, int len);
void				pf_router(t_printf *lst, va_list ap);

#endif
