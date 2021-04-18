/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:48:49 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/23 01:51:31 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_memset_array(void *s, int c, size_t n)
{
	int i;
	unsigned char *str;

	str = s;
	i = 0;
	while (i < (int)n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
