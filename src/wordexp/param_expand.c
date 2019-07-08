/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 20:21:21 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"
#include "ft_patmatch.h"

void			print_array(char **array)
{
	int i;

	i = 0;
	log_info("print array");
	while (array[i])
	{
		log_info("%s", array[i]);
		i++;
	}
}

static size_t	quote_str_len(char *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"') || (str[i] == '\\'))
			count++;
		i++;
	}
	return (count);
}

char			*quote_str(char *str)
{
	size_t	count;
	int		j;
	int		i;
	char	*quoted;

	count = quote_str_len(str);
	i = ft_strlen(str);
	if (!(quoted = ft_strnew(i + count)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"') || (str[i] == '\\'))
		{
			quoted[j] = '\\';
			j++;
		}
		quoted[j] = str[i];
		i++;
		j++;
	}
	return (quoted);
}

char			*check_second_exp_var(char *zone)
{
	char	*var_name;

	var_name = NULL;
	if (ft_strlen(zone) > 2)
		var_name = ft_strsub(zone, 1, ft_strchr(zone, '}') - zone - 1);
	return (var_name);
}

char			*get_var_exp(char *cursor)
{
	char	*var;
	char	*tmp;
	int		len;

	len = 0;
	var = NULL;
	tmp = cursor;
	while (*tmp && *tmp != ':' && *tmp != '}' && *tmp != '%')
	{
		len++;
		tmp++;
	}
	var = ft_strndup(cursor, len);
	return (var);
}
