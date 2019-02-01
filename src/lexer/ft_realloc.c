#include "ft_lexer.h"

int		ft_str_realloc(t_str *str_st, size_t newsz)
{
	char *ptr;

	if (newsz == 0)
		return (0);
	if (!(ptr = ft_memalloc(str_st->size + newsz)))
		return (MEMERR);
	ft_memcpy(ptr, str_st->str, str_st->size);
	str_st->size = str_st->size + newsz;
	free(str_st->str);
	str_st->str = ptr;
	return (0);
}
/*
void	print_st(t_display *display)
{
	ft_printf("oput: %s$$\n", display->oput.str);
	ft_printf("oput sz: %zu\n", display->oput.size);
	ft_printf("olen: %zu\n", display->o_len);
	ft_printf("cursor_pos: %zu\n", display->cursor_pos);
}*/
