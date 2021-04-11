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

void		*ft_removechar(char *str, char c)
{
	int i;
	//int dquote;
	// 쌍따움표가 시작일때 마지막일때 나줘서
	// 그냥 따움표일때
	// 역슬러시 제가 방법 연구
	i = 0;
	while (str[i])
	{
		if (str[(i) - 1] != '\\' && str[i] == c)
		{
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1));
			str[ft_strlen(str) - 1] = 0;
		}
		else
			i++;
	}
	return (str);
}
