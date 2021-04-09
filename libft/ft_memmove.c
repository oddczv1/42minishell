/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:27:01 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/29 00:53:32 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	if (!dest && !src)
		return (0);
	d = dest;
	s = (unsigned char *)src;
	if (src < dest)
		while (n--)
			*(d + n) = *(s + n);
	else
		while (n--)
			*(d++) = *(s++);
	return (dest);
}
