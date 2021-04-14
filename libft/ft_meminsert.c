/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:59:43 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/24 15:00:37 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_meminsert(char *dest, char *src, int end, int start)
{
	char *tem1;
	char *tem2;

	dest[start - 1] = 0;
	tem1 = ft_strjoin(dest, src);
	tem2 = ft_strjoin(tem1, dest + end);
	free(tem1);
	free(dest);
	dest = tem2;
	return (dest);
}
