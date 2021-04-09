/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 19:36:47 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/26 19:42:13 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s)
{
	char	*d;
	int		len;

	len = ft_strlen(s);
	if (!(d = (char*)malloc((len + 1) * sizeof(char))))
		return (0);
	ft_strlcpy(d, s, len + 1);
	return (d);
}
