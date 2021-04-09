/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:45:44 by youngrch          #+#    #+#             */
/*   Updated: 2021/01/02 13:17:37 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t n)
{
	const size_t	srclen = ft_strlen(src);
	size_t			destlen;
	size_t			i;
	char			*s;

	s = (char*)src;
	destlen = ft_strlen(dest);
	if (n < destlen)
		return (srclen + n);
	i = 0;
	while (s[i] && (destlen + i + 1) < n)
	{
		dest[i + destlen] = s[i];
		i++;
	}
	dest[destlen + i] = 0;
	return (destlen + srclen);
}
