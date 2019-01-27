/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:56:36 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:40:18 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BUFF_SIZE 1024

# include <wchar.h>
# include <inttypes.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <locale.h>
# include "libft.h"

typedef	enum	e_lmod
{
	none, hh, h, ll, l, j, z
}				t_lmod;

typedef	enum	e_conversion
{
	s, S, p, d, D, i, o, O, u, U, x, X, c, C, percent
}				t_conversion;

typedef	struct	s_flags
{
	unsigned int	alt_form;
	unsigned int	zero_pad;
	unsigned int	left_adj;
	unsigned int	put_sign;
	unsigned int	space;
	int				min_length;
	int				precision;
	t_lmod			length_mod;
	t_conversion	conversion;
}				t_flags;

int				ft_printf(const char *format, ...);
int				ft_parser(const char **start, t_flags *flags);
int				get_level0(const char **input, t_flags *flags);
int				get_min_len(const char **input, t_flags *flags);
int				get_precision(const char **input, t_flags *flags);
int				get_lmod(const char **input, t_flags *flags);
int				get_conversion(const char **input, t_flags *flags);
int				ft_convert_nbr(t_flags *flags, va_list ap);
int				ft_itoa_base(intmax_t nbr, int base, char *str, int rev);
int				ft_utoa_base(uintmax_t nbr, int base, char *str, int rev);
int				get_signed(t_flags flags, char *buffer, va_list ap);
int				get_unsigned(t_flags *flags, char *buffer, va_list ap);
int				get_base(t_conversion conversion);
void			ft_swap_char(char *a, char *b);
void			ft_strrev(char *str);
int				ft_writebuff(char c, int print);
int				ft_ncpytobuff(char *str, unsigned int n);
void			str_upper(char *str);
void			ft_str_sanity(t_flags *flags);
void			ft_sanity(t_flags *flags);
int				ft_convert_str(t_flags *flags, va_list ap);
void			ft_insert_str(t_flags *flags, char *str);
int				wint_to_mbyte(wint_t toprint, unsigned char *mbyte);
size_t			ft_wcslen(wchar_t *wstr);
void			ft_apply_minlen(t_flags *flags, int tocpy, char padding);
int				ft_insert_wstr(t_flags *flags, wchar_t *wstr);
char			select_padding(t_flags flags);
void			*ft_memcpy(void *dest, const void *src, size_t n);

#endif
