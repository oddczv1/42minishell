/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:54:42 by youngrch          #+#    #+#             */
/*   Updated: 2021/01/02 21:25:46 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count2(char const *s, char c)
{
	int		count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		while (*s != c && *s)
			s++;
		count++;
	}
	return (count);
}

char		*ft_split_dump(char const *s, int len)
{
	char	d[len + 1];
	char	*str;
	int		i;

	i = -1;
	str = (char*)s;
	while (++i < len)
	{
		d[i] = str[i];
	}
	d[i] = 0;
	return (ft_strdup(d));
}

char		**ft_split(char const *s, char c)
{
	const int	count = ft_count2(s, c);
	int			i;
	char		**array;
	char		*word_start;

	if (!s)
		return (0);
	i = -1;
	if (!(array = (char**)malloc((count + 1) * sizeof(char*))))
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		word_start = (char*)s;
		while (*s != c && *s)
			s++;
		array[++i] = ft_split_dump(word_start, s - word_start);
	}
	array[++i] = 0;
	return (array);
}
