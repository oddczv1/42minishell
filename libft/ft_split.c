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

void		ft_find_char(char const *s, int *i, char c)
{
	int start;

	start = *i;
	while (s[start])
	{
		if (s[start] == c)
		{
			(*i)++;
			break ;
		}
		start++;
		(*i)++;
	}
}

void		ft_pass_word(char const *s, char c, int *i)
{
	while (s[(*i)] != c && s[(*i)])
	{
		if (s[(*i)] == '\'')
		{
			(*i)++;
			ft_find_char(s, i, '\'');
		}
		else if (s[(*i)] == '\"')
		{
			(*i)++;
			ft_find_char(s, i, '\"');
		}
		else
			(*i)++;
	}
}

int			ft_count2(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	if (!s)
		return (0);
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		ft_pass_word(s, c, &i);
		count++;
	}
	return (count);
}

char		*ft_split_dump(char const *s, int len)
{
	char	*d;
	char	*str;
	int		i;

	i = -1;
	str = (char*)s;
	d = (char *)malloc(sizeof(char) * (len + 100));
	ft_memset(d, 0, len + 100);
	while (++i < len)
	{
		d[i] = str[i];
	}
	d[i] = 0;
	return (d);
}

char		**ft_split(char const *s, char c)
{
	const int	count = ft_count2(s, c);
	int			x;
	char		**array;
	int			word_start;
	int			i;

	i = 0;
	if (!s)
		return (0);
	x = -1;
	if (!(array = (char**)malloc((count + 1) * sizeof(char*))))
		return (0);
	while (*s)
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		word_start = i;
		ft_pass_word(s, c, &i);
		array[++x] = ft_split_dump(s + word_start, i - word_start);
	}
	array[++x] = 0;
	return (array);
}
