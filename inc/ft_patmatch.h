/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patmatch.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 18:37:40 by tduval            #+#    #+#             */
/*   Updated: 2019/06/26 04:16:04 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PATMATCH_H
# define FT_PATMATCH_H

# define TMP1 0
# define TMP2 1
# define PATTERN 2
# define CURPATTERN 3

# define TMP 0
# define ORIGIN 1

# define FLAG 0
# define COUNTER 1

# define TMP_LST 0
# define SUBTMP_LST 1

typedef	struct	s_lfiles
{
	int				layer;
	char			*path;
	struct s_lfiles	*next;
}				t_lfiles;

char	*ft_strremoveat(char *str, int i);
char	**final_step(t_lfiles *lst, int layer, char *pattern);
char	**sort_files(char **lst);
char	**ret_matches(char *pattern);
char	*get_beginning(char *lpath, char *dname);
char	*after_bracket(char *str);
char	*go_last(char *str);
char	*go_after(char *str);
char	*get_chars(char *str, char c1, char c2);
char	*ft_strapp(char *str, char c);
void	*free_lst(t_lfiles *lst);
void	*free_all(char *str1, char *str2, char *str3, t_lfiles *lst);
int		matches(char *s1, char *s2, int flag);
int		is_in_str(char *str, char c);


#endif
