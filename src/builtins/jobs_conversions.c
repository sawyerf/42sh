/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_conversions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:48:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/26 13:32:02 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** returns ptr on job if found, null otherwise
*/

#include "builtins.h"

t_job	*jobs_conversion(char *arg)
{
	if ((!arg) || (*arg != '%'))
		return (NULL);
	if ((*(arg + 1) == '%') || !(*(arg + 1)))
		return (jobs_conv_pct(arg + 1));
	else if (*(arg + 1) == '+')
		return (jobs_conv_min(arg + 1));
	else if (*(arg + 1) == '-')
		return (jobs_conv_min(arg + 1));
	else if (ft_isalldigit(arg + 1))
		return (jobs_conv_num(arg + 1));
	else if (*(arg + 1) == '?')
		return (jobs_conv_cmd(arg + 1));
	else
		return (jobs_conv_any(arg + 1));
}
