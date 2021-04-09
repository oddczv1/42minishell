/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 19:42:50 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/31 00:19:20 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	size_t	len;

	if (!s1 && !s2)
		return (0);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(d = (char*)malloc((len + 1) * sizeof(char))))
		return (0);
	ft_strlcpy(d, s1, len + 1);
	ft_strlcpy(d + ft_strlen(s1), s2, len + 1);
	return (d);
}
