/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/09 12:15:19 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"
#include "pwd.h"

char	*quote_home(char *str)
{
	size_t	count;
	char	*save;
	char	*new;

	count = count_dollars(str);
	count += ft_strlen(str);
	if (!(new = ft_strnew(count)))
		return (NULL);
	save = new;
	while (*str)
	{
		if (*str == '$')
		{
			*new = '\\';
			new++;
		}
		*new = *str;
		new++;
		str++;
	}
	return (save);
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
		return (ft_strdup(get_env_value("HOME")));
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
	char *save;

	ft_memmove(word->str + *index, word->str + *index + 1, word->len - *index);
	word->len = word->len - 1;
	word->str[word->len] = '\0';
	home = get_home(word, *index);
	if ((!home) || (*home == '\0'))
		return (0);
	save = home;
	if ((add_quote) && (!(home = quote_home(home))))
		return (MEMERR);
	if (insert_str(word, index, home) == MEMERR)
		return (MEMERR);
	if (add_quote)
		free(home);
	free(save);
	return (0);
}
