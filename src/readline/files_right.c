/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:30:23 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/01 18:30:55 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		exaccess(char *file)
{
	struct stat st;

	if (access(file, F_OK))
		return (2);
	stat(file, &st);
	if (S_ISDIR(st.st_mode))
		return (3);
	if (!access(file, X_OK))
		return (0);
	return (1);
}

int		filexist(char *file)
{
	if (access(file, F_OK))
		return (2);
	return (0);
}

int		folexaccess(char *file)
{
	struct stat st;

	if (access(file, F_OK))
		return (2);
	stat(file, &st);
	if (S_ISDIR(st.st_mode))
		return (0);
	if (!access(file, X_OK))
		return (0);
	return (1);
}
