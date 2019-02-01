/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:00:42 by ktlili            #+#    #+#             */
/*   Updated: 2019/01/29 16:42:36 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft.h"

#include <termios.h>
#include <term.h>
#include <termcap.h>
#include <sys/ioctl.h>

#define	INPUTSZ	1024
#define READBUFFSZ 1024
#define MEMERR 1

typedef	struct	s_str
{
	char	*str;
	size_t	size;
}				t_str;

typedef struct	s_display
{
	struct	s_str	oput;
	size_t			o_len;
	size_t			cursor_pos;
	struct winsize	win_sz;
}				t_display;

typedef void	(*t_keypress_fn)(t_display*);

typedef struct	s_keymap
{
	t_keypress_fn	fn;
	char			*code;	
}			t_keymap;



int	init_tcap(void);
int	ft_str_realloc(t_str *str_st, size_t newsz);
void	print_st(t_display *display);
void	map_arrow(char keypress[], t_display *display);
int		handle_char(char c, t_display *display);
void	map_esc(char readbuff[], t_display *display);
int		ft_iputchar(int c);
