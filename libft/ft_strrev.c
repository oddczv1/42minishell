/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 11:16:54 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/25 12:06:32 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	int		n;
	int		j;
	char	tem;
	char	*s;

	n = ft_strlen(str) / 2;
	j = 0;
	s = str;
	while (n--)
	{
		tem = *s;
		*s = *(s + ft_strlen(str) - j - 1);
		*(s + ft_strlen(str) - j - 1) = tem;
		s++;
		j += 2;
	}
	return (str);
}
