#include "ft_wordexp.h"


/*
int	is_expandable(char *cursor)
{

}
*/
int	expand_classic(t_str *s, char **cursor,
		char *value)
{
	int		i;
	int	dummy;
	
	delete_varname(*cursor);
	i = *cursor - s->str;
	dummy = i;
	if (insert_str(s, &dummy, value) == MEMERR)
		return (MEMERR);
	*cursor = s->str + i + ft_strlen(value);
	return (0);
}

int		init_t_str(t_str *s, char *tocpy)
{
	int i;

	i = 0;
	ft_bzero(s, sizeof(t_str));
	if (!(s->str = ft_memalloc(INPUTSZ * sizeof(char))))
		return (MEMERR);
	s->size = INPUTSZ;
	if (insert_str(s, &i, tocpy) == MEMERR)
		return (MEMERR);
	return (0);
}

void	quote_removal_tk(t_str *s)
{
	t_token t;

	ft_bzero(&t, sizeof(t_token));
	ft_memcpy(&t.data, s, sizeof(t_str));
	quote_removal(&t);
}

char	*expand_str(char *cursor)
{
	char	*value;
	t_str	result;
	int		inside_dquote;

	if (init_t_str(&result, cursor))
		return (NULL);
	cursor = result.str;
	inside_dquote = 1;
	while (*cursor)
	{
		if (*cursor == '"')
			inside_dquote = -inside_dquote;
			//should be is expandable
		if ((*cursor == '$') && (*(cursor + 1) != 0))
		{
			value = classic_sub(cursor);	
			if (expand_classic(&result, &cursor, value) == MEMERR)
				return (NULL);
			ft_strdel(&value);
			continue;
		}
		else if ((*cursor == '\'') && (inside_dquote == 1))
			cursor = c_next_squote(cursor);
		else if (*cursor == '\\')
			cursor = c_next_bslash(cursor);
		cursor++;
	}
	quote_removal_tk(&result);
	return (result.str);
}
