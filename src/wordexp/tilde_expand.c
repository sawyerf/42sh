/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 17:30:23 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"
#include "pwd.h"

int		tilde_valid(char c)
{
	if (ft_isalpha(c))
		return (1);
	if ((c == 0) || (c == '/') || (c == ':'))
		return (1);
	return (0);
}

char	*quote_home(char *str)
{
	char *new;

	new = ft_strnew(ft_strlen(str) + 2);
	if (!new)
		return (NULL);
	new[0] = '\'';
	ft_strcpy(new + 1, str);
	new[ft_strlen(new)] = '\'';
	return (new);
}

char	*get_userhome(char *user)
{
	struct passwd *info;

	if (!(info = getpwnam(user)))
		return (NULL);
	return (info->pw_dir);
}

char	*get_home(t_str *word, int i)
{
	char	*user;
	char	*home;

	if ((ft_cisin("/ \t\n\r", word->str[i])) || !(word->str[i]))
		return (get_env_value("HOME"));
	while (!ft_cisin("/ \t\n\r", word->str[i]) && word->str[i])
		i++;
	if (!(user = ft_strndup(word->str, i)))
		return (NULL);
	home = get_userhome(user);
	ft_strdel(&user);
	if (!home)
	{
		if (!(home = ft_zprintf("~%s", word->str)))
			return (NULL);
		ft_strdel(&word->str);
		word->str = home;
		return (NULL);
	}
	ft_memmove(word->str, word->str + i + 1, i);
	word->len = word->len - i;
	return (home);
}

int		expand_tilde(t_str *word, int *index, int add_quote)
{
	char *home;

	ft_memmove(word->str + *index, word->str + *index + 1, word->len - *index);
	word->len = word->len - 1;
	word->str[word->len] = '\0';
	home = get_home(word, *index);
	if ((!home) || (*home == '\0'))
		return (0);
	if ((add_quote) && (!(home = quote_home(home))))
		return (MEMERR);
	if (insert_str(word, index, home) == MEMERR)
		return (MEMERR);
	if (add_quote)
		free(home);
	return (0);
}
