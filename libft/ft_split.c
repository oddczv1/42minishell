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

void		ft_find_char(char const *s, int *i, int *token, char c)
{
	int start;

	start = *i;
	while (s[start])
	{
		if (s[start] == c)
		{
			*token = 0;
			break ;
		}
		start++;
		(*i)++;
	}
}

int			ft_count2(char const *s, char c)
{
	int		count;
	int		q;
	int		dq;
	int		i;

	q = 0;
	dq= 0;
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
		while (s[i] != c && s[i])
		{
			if (s[i] == '\'' && q == 0 && dq == 0)
			{
				q = 1;
				i++;
			}
			if (s[i] == '\"' && q == 0 && dq == 0)
			{
				dq = 1;
				i++;
			}
			if (q == 1 && dq == 0)
				ft_find_char(s, &i, &q, '\'');
			else if (q == 0 && dq == 1)
				ft_find_char(s, &i, &dq, '\"');	
			else
				i++;
		}
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
	int			x;
	char		**array;
	int		word_start;
	int		q;
	int		dq;
	int		i;

	i = 0;
	q = 0;
	dq = 0;
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
		while (s[i] != c && s[i])
		{
			if (s[i] == '\'' && q == 0 && dq == 0)
				q = 1;
			if (s[i] == '\"' && q == 0 && dq == 0)
				dq = 1;
			if (q == 1 && dq == 0)
				ft_find_char(s, &i, &q, '\'');
			else if (q == 0 && dq == 1)
				ft_find_char(s, &i, &dq, '\"');	
			else
				i++;
		}
		array[++x] = ft_split_dump(s + word_start, i - word_start);
	}
	array[++x] = 0;
	return (array);
}

#include <stdio.h>

int main()
{
	char *a = "   aaaa;     bbbb;     '   ;   ';      ";
	char **b;
	b = ft_split(a, ';');
	int j = -1;
	while (b[++j])
	{
		printf("%s\n", b[j]);
	}
	return 0;
}