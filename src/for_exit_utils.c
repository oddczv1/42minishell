/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_exit_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 20:48:22 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/26 20:50:16 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		case_plus(char *str)
{
	char	*max;
	int		ret;

	max = ft_strdup("9223372036854775807");
	if (ft_strlen(str) < 19)
		ret = 1;
	else if (ft_strlen(str) == 19)
	{
		if (ft_strncmp(max, str, 20) >= 0)
			ret = 1;
		else
			ret = 0;
	}
	else
		ret = 0;
	free(max);
	return (ret);
}

int		case_minus(char *str)
{
	char	*min;
	int		ret;

	min = ft_strdup("-9223372036854775809");
	if (ft_strlen(str) < 20)
		ret = 1;
	else if (ft_strlen(str) == 20)
	{
		if (ft_strncmp(min, str, 21) >= 0)
			ret = 1;
		else
			ret = 0;
	}
	else
		ret = 0;
	free(min);
	return (ret);
}

int		is_inside(char *str)
{
	int minus;

	if (str[0] == '-')
		minus = 1;
	else
		minus = 0;
	if (!minus)
		return (case_plus(str));
	else
		return (case_minus(str));
}
