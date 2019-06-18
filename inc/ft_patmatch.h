/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patmatch.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 18:37:40 by tduval            #+#    #+#             */
/*   Updated: 2019/06/18 20:51:18 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PATMATCH_H
# define FT_PATMATCH_H

typedef	struct	s_lfiles
{
	int				layer;
	char			*path;
	struct s_lfiles	*next;
}				t_lfiles;

char	**ret_matches(char *pattern);
char	*after_bracket(char *str);
char	*get_chars(char *str, char c1, char c2);
char	*ft_strapp(char *str, char c);
int		matches(char *s1, char *s2);
int		is_in_str(char *str, char c);

#endif
