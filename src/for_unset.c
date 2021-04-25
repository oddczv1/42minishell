/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:07:29 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/24 15:07:31 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_unset(t_data *data)
{
	if (data->cmd[1])
		delete_env(data, data->cmd[1]);
	get_paths(data);
	recover_std(data);
}
