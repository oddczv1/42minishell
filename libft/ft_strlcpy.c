/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:06:33 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/29 10:52:17 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t srcsize;
	size_t i;

	if (dest == 0 || src == 0)
		return (0);
	srcsize = ft_strlen(src);
	i = 0;
	if (n != 0)
	{
		while (i < n - 1 && src[i] != 0)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (srcsize);
}
