/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:02:45 by ktlili            #+#    #+#             */
/*   Updated: 2018/12/13 19:05:02 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_readline.h"

int	ft_iputchar(int c)
{
	if (write(0, &c, 1) < 0)
		return (-1);
	return (0);
}

void	tc_cursorl(void)
{
	static char	*le = NULL;

	if (!le)
		le = tgetstr("le", NULL);
	tputs(le, 1, ft_iputchar);
}

void	tc_cursorr(void)
{
	static char	*nd = NULL;

	if (!nd)
		nd = tgetstr("nd", NULL);
	tputs(nd, 1, ft_iputchar);
}

void	left_press(t_display *display)
{
	if (display->cursor_pos == 0)
		return;
	tc_cursorl();
	display->cursor_pos = display->cursor_pos - 1;
}

void	right_press(t_display *display)
{
	if (display->cursor_pos >= display->o_len)
		return;
	tc_cursorr();
	display->cursor_pos = display->cursor_pos + 1;
}

void	tc_delete(t_display *display)
{
	static char *del = NULL;
	
	if (!del)
		del = tgetstr("dc", NULL);
	tputs(del, 1, ft_iputchar);
}

void	delete_press(t_display *display)
{
	if (display->cursor_pos >= display->o_len)
		return;
	tc_delete(display);
	display->o_len--;
		
}

void	bspace_press(t_display *display)
{	
	if (display->cursor_pos == 0)
		return;
	left_press(display);
	delete_press(display);
}
void	tc_bspace(t_display *display)
{
	static char *bspace = NULL;

	if (!bspace)
		bspace = tgetstr("kb", NULL);

}

#define MAXKEYS 4

static void	init_keymap(t_keymap keymap[MAXKEYS])
{
	size_t	i;
	static t_keypress_fn	fnarray[] = {left_press, right_press, delete_press
										, bspace_press, NULL};

	i = 0;
	keymap[i].fn = fnarray[i];
	keymap[i++].code = "\x1b\x5b\x44" ; //tgetstr("kl", NULL);
	keymap[i].fn = fnarray[i];
	keymap[i++].code =  "\x1b\x5b\x43" ;//tgetstr("kr", NULL);
	keymap[i].fn = fnarray[i];
	keymap[i++].code = tgetstr("kD", NULL);
	keymap[i].fn = fnarray[i];
	keymap[i++].code = "\x7f";//tgetstr("kb", NULL);	
}

void	map_esc(char read_buff[READBUFFSZ], t_display *display)
{

	static	t_keymap	keymap[MAXKEYS];
	static	int			init_flag = 0;
	size_t				index;

	if (!init_flag)
	{
		init_flag = 1;
		init_keymap(keymap);
	}
	index = 0;
	while (index < MAXKEYS)
	{
		if (!ft_strcmp(keymap[index].code, read_buff))
			keymap[index].fn(display);	
		index++;
	}
}
/*
void	map_arrow(char keypress[10], t_display *display)
{
	if (keypress[2] == 'A')
	{
	//	ft_printf("Up!");
	}
	else if (keypress[2] == 'B')
	{
	//	ft_printf("Down!");
	}
	else if (keypress[2] == 'D')
	{
		left_press(display);
	}
	else if (keypress[2] == 'C')
	{
		right_press(display);
	}
	else 
	{
		delete_press(keypress, display);
	}
}*/
