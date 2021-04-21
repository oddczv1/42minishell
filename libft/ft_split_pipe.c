/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_semi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:08:51 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/09 23:08:56 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_space_pipe(char *str)
{
	if (*str == '|')
	{
		if (*(str - 1) == '\\')
			return (0);
		return (1);
	}
	return (0);
}

int		count_word_pipe(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		while (is_space_pipe(str))
			str++;
		if (*str == '\0')
			break ;
		while (!is_space_pipe(str) && *str != '\0')
			str++;
		count++;
	}
	return (count);
}

char	*ft_strndup_pipe(char *str, unsigned int n)
{
	unsigned int	i;
	char			*dup;

	dup = (char*)malloc((n + 3) * sizeof(char));
	i = 0;
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	**ft_split_pipe(char *str)
{
	int		i;
	int		word_count;
	char	*word_start;
	char	**array;

	if (!str)
		return (0);
	word_count = count_word_pipe(str);
	array = (char**)malloc((word_count + 1) * sizeof(char *));
	i = 0;
	while (*str)
	{
		while (is_space_pipe(str))
			str++;
		if (*str == '\0')
			break ;
		word_start = str;
		while (!is_space_pipe(str) && *str != '\0')
			str++;
		array[i] = ft_strndup_pipe(word_start, str - word_start);
		i++;
	}
	array[i] = 0;
	return (array);
}
