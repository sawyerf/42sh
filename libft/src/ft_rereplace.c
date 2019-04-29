/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rereplace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:34:23 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/15 22:36:34 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_rereplace(char *str, char *to, char *by)
{
	char	*tmp;

	tmp = ft_replace(str, to, by);
	ft_strdel(&str);
	return (tmp);
}
