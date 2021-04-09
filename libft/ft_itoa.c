/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 10:08:15 by youngrch          #+#    #+#             */
/*   Updated: 2020/12/29 12:56:09 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count1(int n, char manus)
{
	int	count;

	count = 0;
	if (manus || !n)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	const int	manus = (n < 0);
	int			count;
	char		*d;
	int			i;

	count = ft_count1(n, manus);
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (!(d = (char*)ft_calloc(count + 1, sizeof(char))))
		return (0);
	if (manus)
		n *= -1;
	i = -1;
	while (++i < count)
	{
		d[count - i - 1] = (n % 10) + '0';
		n /= 10;
	}
	if (manus)
		d[0] = '-';
	return (d);
}
