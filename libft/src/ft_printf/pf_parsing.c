/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:09:01 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/07 16:36:20 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_passnb(const char *str, int *count)
{
	int tmp;

	if (str[*count] == '*')
		tmp = -1;
	else
		tmp = ft_atoi(&str[*count]);
	if (!(str[*count] >= '0' && str[*count] <= '9') && str[*count] != '*')
	{
		(*count)--;
		return (tmp);
	}
	while ((str[*count + 1] >= '0' && str[*count + 1] <= '9'))
		(*count)++;
	return (tmp);
}

void		pf_point(t_printf *lst, const char *str, int *count)
{
	(*count)++;
	lst->pre[2] = 1;
	lst->pre[1] = pf_passnb(str, count);
}

t_printf	*analyze(const char *str, int *count)
{
	t_printf	*lst;

	if (!(lst = pf_prnew(NULL, 1)))
		return (NULL);
	while (str[*count])
	{
		if ((str[*count] >= '1' && str[*count] <= '9') || str[*count] == '*')
			lst->pre[0] = pf_passnb(str, count);
		else if (str[*count] == '.')
			pf_point(lst, str, count);
		else if (ft_cisin("-+#0 ", str[*count]))
			(!ft_cisin(lst->settings, str[*count])) ? ft_strncat(lst->settings,
					&str[*count], 1) : 0;
		else if (ft_cisin("lhzj", str[*count]))
			(ft_strlen(lst->size) < 2) ? ft_strncat(lst->size,
					&str[*count], 1) : 0;
		else
			break ;
		(*count)++;
	}
	if (!str[*count])
		return (NULL);
	lst->type = str[*count];
	return (lst);
}

void		pf_set(const char **str, int *count, int n)
{
	*str += *count + 1;
	*count = n;
}

t_printf	*pf_parser(const char *str)
{
	int			count;
	t_printf	*lst;
	t_printf	*tmp;

	lst = NULL;
	count = 0;
	while (str[count])
	{
		if (str[count] == '%')
		{
			if (!str[count + 1])
				return (NULL);
			if (count)
				lst = ft_pushback(lst, pf_prnew(ft_strndup(str, count), 0));
			pf_set(&str, &count, 0);
			if (!(tmp = analyze(str, &count)))
				return (NULL);
			lst = ft_pushback(lst, tmp);
			pf_set(&str, &count, -1);
		}
		count++;
	}
	if (count)
		lst = ft_pushback(lst, pf_prnew(ft_strndup(str, count), 0));
	return (lst);
}
