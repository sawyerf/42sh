/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 06:40:12 by tduval            #+#    #+#             */
/*   Updated: 2019/06/29 06:41:44 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strremoveat(char *str, int i)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (j >= i)
			str[j] = str[j + 1];
		else
			str[j] = str[j];
		j++;
	}
	return (str);
}

int		get_layer(char *pattern)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (pattern[i])
	{
		if (pattern[i] == '/' && pattern[i + 1] && pattern[i + 1] != '/')
			r++;
		i++;
	}
	return (r);
}

char	*format_pattern(char *pattern)
{
	int		i;

	i = 0;
	while (pattern && pattern[i])
	{
		if (pattern[i] == '.'
				&& pattern[i + 1] == '/'
				&& (i == 0 || pattern[i - 1] == '/'))
		{
			pattern = ft_strremoveat(pattern, i);
			pattern = ft_strremoveat(pattern, i);
		}
		else
			i++;
	}
	return (pattern);
}
