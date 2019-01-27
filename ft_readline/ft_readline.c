/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:00:46 by ktlili            #+#    #+#             */
/*   Updated: 2018/12/13 18:05:36 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_readline.h"

int		handle_char(char c, t_display *display)
{
	size_t index;

	index = display->o_len;
	if (display->o_len == display->oput.size)
		if (ft_str_realloc(&(display->oput), INPUTSZ) == MEMERR)
			return (MEMERR);
	display->oput.str[index] = c;
	display->o_len = display->o_len + 1;
	display->cursor_pos = display->cursor_pos + 1;
	write(STDOUT_FILENO, &c, 1);
	return (0);
}

/*
int		get_esc(char keypress[10], t_display *display)
{
	if (read(STDIN_FILENO, keypress + 1, 1) == 1)
	{
		if (keypress[1] == '[')		
		{
			if (read(STDIN_FILENO, keypress + 2, 1) == 1)
			{
				if (keypress[2] > 'A') && (keypress[2]
				map_arrow(keypress, display);
				ft_bzero(keypress, 10);
				return (0);
			}
			return (2);
		}
		else
			return (-1);
	}
	return (-1);
	
}


int		map_key(t_display *display, char c)
{
	char	keypress[10];
	int		i;

	ft_bzero(keypress, 10);
	if (c == '\x1b')
	{
		keypress[0] = '\x1b';
		if ((get_esc(keypress, display) == -1) )
		{
		//	print_st(display);
		//	exit(1);
			//do what esc does here
			return (0);
		}
		i = 0;
		while (keypress[i])
		{
			handle_char(keypress[i], display);
			i++;
		}
		return (0);
	}
	handle_char(c, display);
	return (0);
	
}
*/
int map_key(t_display *display, char read_buff[READBUFFSZ])
{
	size_t	i;

	i = 1;
	if ((read_buff[0] == '\x1b') || (read_buff[0] == '\x7f'))
	{
		while (read(STDIN_FILENO, &(read_buff[i++]), 1) == 1)
		{
			if (i == READBUFFSZ)
					break;
		}
		map_esc(read_buff, display);
		ft_bzero(read_buff, READBUFFSZ);
		return (0);
	}
	handle_char(read_buff[0], display);
	return (0);
}

static int		init_display(t_display *display)
{

	ft_bzero(display, sizeof(t_display));
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &(display->win_sz)) == -1)
		return (MEMERR); //change to sys call fail
	if (!(display->oput.str = ft_memalloc(INPUTSZ * sizeof(char))))
		return (MEMERR);
	display->oput.size = INPUTSZ; 
	return (0);
}
/*
we need g_errno??
*/
char	*readline(const char *prompt)
{
	char		c;
	char		read_buff[READBUFFSZ];
	t_display	display;
	int			read_ret;

	if (init_display(&display))
		return (NULL);
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	while (42)
	{
		ft_bzero(read_buff, READBUFFSZ);
		if (((read_ret = read(STDIN_FILENO, read_buff, 1)) == -1))
			break;
		else if (read_ret == 1)
			map_key(&display, read_buff);	
	}
	//handle -1 here
}

int main()
{
	char *line;

	init_tcap();
	line = readline("42$>");
}
