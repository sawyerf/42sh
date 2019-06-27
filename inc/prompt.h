/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:06:10 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/27 19:57:40 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <unistd.h>
# include "libft.h"
# include "sh_core.h"

typedef struct		s_prompt
{
	char			p;
	void			(*f)(t_stri *str, char p);
}					t_prompt;

char				*prompt(char *ps1);
void				pr_gene(t_stri *str, char p);
void				pr_w(t_stri *str, char p);
void				pr_version(t_stri *str, char p);

#endif
