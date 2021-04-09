/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:09:47 by youngrch          #+#    #+#             */
/*   Updated: 2021/01/02 10:14:01 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_number(char *s, unsigned long long *number)
{
	while (s)
	{
		if (*s >= '0' && *s <= '9')
		{
			*number *= 10;
			*number += (*s - '0');
		}
		else
			break ;
		s++;
	}
}

char		*ft_atoi_manus(char **s, int *manus)
{
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			*manus *= -1;
		(*s)++;
	}
	return (*s);
}

int			ft_atoi(const char *str)
{
	char				*s;
	int					manus;
	unsigned long long	number;

	manus = 1;
	number = 0;
	s = (char*)str;
	while (s)
	{
		if (!(*s == ' ' || (*s >= 9 && *s <= 13)))
			break ;
		s++;
	}
	ft_atoi_manus(&s, &manus);
	ft_number(s, &number);
	if (number > LONG_MAX - 1 && manus == -1)
		return (0);
	if (number > LONG_MAX - 2 && manus == 1)
		return (-1);
	return (manus * number);
}
