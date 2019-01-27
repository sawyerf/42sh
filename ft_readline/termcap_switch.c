#include "../ft_readline.h"

static struct termios	*termios_save(struct termios *termios_st)
{
	static	struct termios	save_termios;

	if (termios_st != NULL)
		ft_memcpy(&save_termios, termios_st, sizeof(struct termios));
	return (&save_termios);
}

struct termios	*termios_set(void)
{
	static	struct termios	curr_termios;
	static	int		flag = 1;

	if (flag)
	{
		flag = 0;
		if (tcgetattr(0, &curr_termios) != 0)
		{
			//undo_caps();
			exit(1);
		}
		termios_save(&curr_termios);
	}
	return (&curr_termios);
}

int		tc_insert_mode(int on)
{
	static char	*im = NULL;
	static char	*ei = NULL;
	if ((!im) || (!ei))
	{
		ei = tgetstr("ei", NULL);
		im = tgetstr("im", NULL);
		if ((!im) || (!ei))
			return (-1);
	}
	if (on)
		tputs(im, 1, ft_iputchar);
	else
		tputs(ei, 1, ft_iputchar);
	return (0);
}

int	init_tcap(void)
{
	char 			*term;
	struct	termios	*termios_st;

	if (((term = getenv("TERM")) == NULL) || (tgetent(NULL, term) <= 0))
	{
		ft_printf("term is dumb\n");
		return (-1);
	}
	tc_insert_mode(1);
	termios_st = termios_set();
	termios_st->c_lflag &= ~(ICANON);
	termios_st->c_cc[VMIN] = 0; /*min chars to read */
	termios_st->c_cc[VTIME] = 0;
	termios_st->c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSANOW, termios_st) != 0)
	{
		exit(1);
	}
	return (0);	
}

int restore_tcap(void)
{
	struct	termios	*save;

	save = termios_save(NULL);
	//undo_caps();
	tcsetattr(0, TCSANOW, save);
	return (0);
}
