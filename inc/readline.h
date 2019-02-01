/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:50:56 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/01 18:47:18 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H
# include "libft.h"
# include <curses.h>
# include <termios.h>
# include <term.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <fcntl.h>

# define K_UP	"\33[A"
# define K_LEFT	"\33[D"
# define K_RGHT	"\33[C"
# define K_DWN	"\33[B"
# define K_SPC	" "
# define K_ENTR	"\012"
# define K_BSPC "\177"
# define K_DEL	"\33[3~"
# define K_ESC	"\33"
# define K_CTRA	"\1"
# define K_CTRD	"\4"

typedef struct		s_rdl
{
	char			*str;
	int				size;
	int				allo;

	int				curs;
}					t_rdl;

typedef struct		s_key
{
	char			*key;
	void			(*f)(t_rdl *rdl, char *key);
}					t_key;

//main
char				*readline(char	*PROMPT);

//termcaps
int		terminit(struct termios *save);

//keys
void    key_router(t_rdl *rdl, char *buf);
void	del_cara(t_rdl *rdl, char *buf);
void	special_key(t_rdl *rdl, char *buf);
void	begin(t_rdl *rdl, char *buf);
void	move_curs(t_rdl *rdl, char *buf);

//tools
int		is_special(char *buf);

//struct rdl
void				rdlinit(t_rdl *rdl);
void	rdladd(t_rdl *rdl, char c);
void	rdldel(t_rdl *rdl, int curs);
#endif
