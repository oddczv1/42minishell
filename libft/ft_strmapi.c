/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:30:52 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/28 14:01:48 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*d;
	size_t	i;

	if (!s || !f || !(d = ft_strdup(s)))
		return (0);
	i = 0;
	while (d[i])
	{
		d[i] = f(i, d[i]);
		i++;
	}
	return (d);
}
