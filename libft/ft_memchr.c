/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:23:30 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/24 15:02:01 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *ptr, int value, size_t n)
{
	unsigned char *p;

	p = (unsigned char*)ptr;
	while (n--)
	{
		if (*p == (unsigned char)value)
		{
			return ((void *)p);
		}
		p++;
	}
	return (0);
}
