/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_removechar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:59:43 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/22 16:44:57 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_check_escape_num1(char *str, int i)
{
    int num;

    num = 0;
    if (str[i] == '\'' || str[i] == '\"')
    {
        while(str[--i] == '\\')
            ++num;
    }
    num = num % 2;
    return (num);
}

void		ft_removechar_2(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ( c == '\"')
		{
			if (!ft_check_escape_num1(str, i) && str[i] == c)
			{
				ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1));
				str[ft_strlen(str) - 1] = 0;
			}
			else
				i++;
		}
	}
}

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
				i++;
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
