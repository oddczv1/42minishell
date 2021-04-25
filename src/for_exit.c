/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:54:45 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/25 16:02:06 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_exit(t_data *data)
{
	int		idx;
	char	*str;

	if (data->cmd[1] == NULL)
		exit(0);
	else
	{
		str = data->cmd[1];
		idx = 0;
		while (str[idx])
		{
			if (ft_isdigit(str[idx]))
				idx++;
			else
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("bash: exit: ", 2);
				ft_putstr_fd(data->cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
		}
		exit(ft_atoi(str));
	}
}
