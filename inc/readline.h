/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:50:56 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/11 20:17:27 by apeyret          ###   ########.fr       */
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
# include <sys/signal.h>
# include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

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
# define K_CTRC	"\3"
# define K_CTRD	"\4"
# define K_SLFT "\33[1;2D"
# define K_SRGT "\33[1;2C"
# define K_TAB	"\t"

typedef struct		s_rdl
{
	char			*str;
	int				size;
	int				allo;

	char			*prompt;
	struct termios		save;
	int				curs;
	int				col;
	int				lpro;
}					t_rdl;

typedef struct		s_hash
{
	char			*exec;
	char			*path;
}					t_hash;

typedef struct		s_key
{
	char			*key;
	int				(*f)(t_rdl *rdl, char *key);
}					t_key;

//main
char				*readline(char	*PROMPT);

//hashtable
void	ht_init(void);
int		ht_hash(char *path);
t_list	*ht_get(char *path);
t_list	*ht_getexec(char *path);
void	ht_refreshall(char *path);

//termcaps
int		terminit(struct termios *save);
int		getcolumn(void);
int		termreset(struct termios *save);
void	tgpstr(char *s);

//keys
int	    key_router(t_rdl *rdl, char *buf);
int		next_word(t_rdl *rdl, char *buf);
int		prev_word(t_rdl *rdl, char *buf);
int		del_cara(t_rdl *rdl, char *buf);
int		special_key(t_rdl *rdl, char *buf);
int		begin(t_rdl *rdl, char *buf);
int		move_curs(t_rdl *rdl, char *buf);
int		enter(t_rdl *rdl, char *buf);
int		ctrld(t_rdl *rdl, char *buf);
int		ctrlc(t_rdl *rdl, char *buf);
int		autocompl(t_rdl *rdl, char *buf);

//tools
int		is_special(char *buf);
void	left(t_rdl *rdl, int i);
void	right(t_rdl *rdl, int i);

//file
t_list	*get_exec(char *exec, char *path);
t_list	*get_folex(char *token);
int		folexaccess(char *file);

//struct rdl
void				rdlinit(t_rdl *rdl, char *PROMPT);
void	rdladd(t_rdl *rdl, char c);
void	rdldel(t_rdl *rdl, int curs);
void	rdladdstr(t_rdl *rdl, char *str);

//signal
void	setsig(void);

//print
void	putlst(char *mtc, t_list *lst, t_rdl *rdl);
#endif
