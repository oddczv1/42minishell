/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:48:49 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/24 14:49:13 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_data *data)
{
	if (!ft_strncmp(data->cmd[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "env", 4))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "export", 7))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "bash", 5))
		return (1);
	else
		return (0);
}
