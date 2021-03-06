/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <apeyret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:26:00 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/25 16:41:46 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "libft.h"
# include "ft_eval.h"

# define HT_SIZE 2048

typedef enum	e_binerr
{
	br_OK = 0,
	br_PERMDENIED = 1,
	br_NOTFOUND = 2,
	br_ISDIR = 3,
	br_PATHNOTSET = 4,
	br_PARAMETER = 5,
}				t_binerr;

int		exaccess(char *file);
int		ht_init(void);
int		ht_hash(char *path);
t_list	*ht_get(char *path);
int		ht_getexec(char *path, t_list **lst);
int		ht_spawnbin(char *path, t_cmd_tab *cmd);
void	ht_del(void);
int		ht_getfile(char **paths, char *cmd, char **fullpath);
int		ht_refreshall(char *path);
t_list	**ht_gget(void);
int		ht_addfile(char	**paths, char *exec);
char	*ht_getpath(char **path, char *exec);
int		ht_addpath(char *path, char *npath);

#endif
