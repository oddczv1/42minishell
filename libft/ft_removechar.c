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

void		ft_removechar(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ( c == '\\')
		{
			if (str[i] == c && str[(i) + 1] == '\\')
			{
				ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1));
				str[ft_strlen(str) - 1] = 0;
			}
			else
				i++;	
		}
		else
		{
			if (str[(i) - 1] != '\\' && str[i] == c )
			{
				ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1));
				str[ft_strlen(str) - 1] = 0;
			}
			else
				i++;	
		}
	}
}
