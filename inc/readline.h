/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:50:56 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/12 18:09:19 by ktlili           ###   ########.fr       */
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
# include <dirent.h>
# include <sys/stat.h>
# include "ft_eval.h"

# define K_SUP  "\33[1;2A"
# define K_SDOW "\33[1;2B"
# define K_SRGT "\33[1;2C"
# define K_SLFT "\33[1;2D"
# define K_DEL	"\33[3~"
# define K_UP	"\33[A"
# define K_LEFT	"\33[D"
# define K_RGHT	"\33[C"
# define K_DOWN	"\33[B"
# define K_END  "\33[F"
# define K_HOME "\33[H"
# define K_TAB	"\t"
# define K_CTRA	"\1"
# define K_CTRC	"\3"
# define K_CTRD	"\4"
# define K_ENTR	"\12"
# define K_ENTD	"\r"
# define K_CTRR	"\22"
# define K_CTRP	"\20"
# define K_CTRV	"\26"
# define K_CTRX	"\30"
# define K_CTRY	"\31"
# define K_ESC	"\33"
# define K_SPC	" "
# define K_BSPC "\177"

typedef struct		s_rdl
{
	struct termios	save;
	char			*prompt;
	int				curs;
	int				real;
	int				col;
	int				lpro;

	char			*str;
	int				size;
	int				allo;

	int				vcurs;
	char			*paste;
}					t_rdl;

typedef struct		s_key
{
	char			*key;
	int				(*f)(t_rdl *rdl, char *key);
}					t_key;

int					readline(char *prompt, char **str);

int					terminit(struct termios *save);
int					getcolumn(void);
int					termreset(struct termios *save);
void				tgpstr(char *s);
void				get_cursor_position(int *col, int *rows);

int					special_key(t_rdl *rdl, char *buf, t_key *key);
int					key_router(t_rdl *rdl, char *buf);
int					next_word(t_rdl *rdl, char *buf);
int					prev_word(t_rdl *rdl, char *buf);
int					del_cara(t_rdl *rdl, char *buf);
int					ddel_cara(t_rdl *rdl, char *buf);
int					begin(t_rdl *rdl, char *buf);
int					move_curs(t_rdl *rdl, char *buf);
int					enter(t_rdl *rdl, char *buf);
int					ctrld(t_rdl *rdl, char *buf);
int					ctrlc(t_rdl *rdl, char *buf);
int					autocompl(t_rdl *rdl, char *buf);
int					visualmode(t_rdl *rdl, char *buf);
int					vm_move(t_rdl *rdl, char *buf);
int					vm_copy(t_rdl *rdl, char *buf);
int					vm_del(t_rdl *rdl, char *buf);
int					vm_cut(t_rdl *rdl, char *buf);
int					paste(t_rdl *rdl, char *buf);
int					finish(t_rdl *rdl, char *buf);
int					end(t_rdl *rdl, char *buf);
int					history(t_rdl *rdl, char *buf);
int					ctrlr(t_rdl *rdl, char *buf);
int					normal_key(t_rdl *rdl, char *buf);
int					ctrlr(t_rdl *rdl, char *buf);
t_list				*get_cplenv(char *match);
int					k_hstret(t_rdl *rdl, char *buf);

void				reprint(t_rdl *rdl, int curs);
int					is_special(char *buf);
int					left(t_rdl *rdl, int i);
int					right(t_rdl *rdl, int i);
int					up(t_rdl *rdl, int i);
int					down(t_rdl *rdl, int i);
void				lastcol(t_rdl *rdl);

t_list				*get_exec(char *exec, char *path);
t_list				*get_folex(char *token, int (*f)(char *file));
int					folexaccess(char *file);
int					exaccess(char *file);
int					filexist(char *file);

int					rdlinit(t_rdl *rdl, char *prompt);
void				rdladd(t_rdl *rdl, char c);
void				rdldel(t_rdl *rdl, int curs);
void				rdladdstr(t_rdl *rdl, char *str);
void				rdlreplace(t_rdl *rdl, char *s);

void				setsig(void);

void				putlst(char *mtc, t_list *lst, t_rdl *rdl);

t_list				*gethst(void);
void				hstadd(char *str);
char				*hstnext(char *s);
char				*hstprev(void);
void				hstreset(void);
char				*hstchc(char *s);
void				hstaddfile(char **env);
int					hstread(char **env);
int					hstnchc(t_rdl *rdl, char *buf);
int					hstdelcara(t_rdl *rdl, char	*buf);
t_list				*hst_getcmp(t_list *lst, char *s);
t_list				*hst_pgetcmp(t_list *lst, char *s);
void				hstdellast();

#endif
