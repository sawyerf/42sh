/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:50:56 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/03 21:12:36 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H
# include "libft.h"

# define MEMERR -1001

typedef struct		s_stri
{
	int				curs;
	char			*str;
	int				size;
	int				allo;
}					t_stri;

int					str_init(t_stri *str);
int					str_add(t_stri *str, char c);
int					str_addstr(t_stri *str, char *s);
int					str_del(t_stri *str, int curs);
int					str_replace(t_stri *str, char *to, char *by);
int					str_replaceall(t_stri *str, char *s);

#endif
