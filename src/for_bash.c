/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_bash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:24 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/24 15:32:46 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_bash(t_data *data)
{
	if (fork() == 0)
		execve("/bin/bash", data->cmd, data->env);
	else
		wait(NULL);
	recover_std(data);
}
