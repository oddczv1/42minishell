/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:54:45 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/26 19:33:08 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_numeric(char *str)
{
	int	idx;

	idx = 0;
	if (ft_isdigit(str[idx]) || str[idx] == '-' || str[idx] == '+')
		idx++;
	while (str[idx])
	{
		if (ft_isdigit(str[idx]))
			idx++;
		else
			return (0);
	}
	return (1);
}

void	many_arg(t_data *data)
{
	int	head_is_numeric;

	head_is_numeric = is_numeric(data->cmd[1]);
	if (head_is_numeric == 1)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_t.status = 1;
		data->flag = 1;
		recover_std(data);
	}
	else
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(data->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
}

int		is_inside(long long num)
{
	//printf("%")
	if (num > 0)
	{
		if (num <= (long long)(9223372036854775807LL))
			return (1);
	}
	else
	{
		//num *= -1;
		if (num >= (long long)(0xFFFFFFFFFFFFFFFF))
			return (1);
	}
	return (0);


	//if ((long long)(9223372036854775808LL) * (-1LL)<= num && num <= (long long)9223372036854775807LL)
//		return (1);
//	else
//		return (0);
}

void	process_exit(t_data *data)
{
	int		idx;
	char	*str;

	ft_putstr_fd("exit\n", 1);
	idx = 0;
	if (data->cmd[1] == NULL)
		exit(0);
	else if (data->cmd[2] != NULL)
		many_arg(data);
	else
	{
		str = data->cmd[1];
		if (is_numeric(str) && is_inside(ft_atoi(str)))
			exit(ft_atoi(data->cmd[1]));
		else
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(data->cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
}
