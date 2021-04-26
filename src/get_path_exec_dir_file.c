/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_exec_dir_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:05:34 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/26 15:50:10 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	path_to_file(t_data *data, t_path_var *var)
{
	var->flag = 1;
	ft_strlcpy(var->str, data->cmd[0], 300);
	*(var->p) = 0;
	ft_strlcpy(var->temp_dir, data->cmd[0], 300);
	var->temp_file = ft_strdup(var->p + 1);
	free(data->cmd[0]);
	data->cmd[0] = var->temp_file;
}

static	int		path_err(t_data *data, t_path_var *var)
{
	char	*temp;

	if (!ft_relative_path_check(data, var) && var->flag == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(var->str, 2);
		ft_putstr_fd(": No such file or directory", 2);
		write(2, "\n", 1);
		g_t.status = 1;
		data->flag = 1;
		return (1);
	}
	ft_strlcpy(data->exec_dir, data->paths[var->idx], 300);
	temp = ft_strjoin(data->exec_dir, "/");
	ft_strlcpy(data->exec_dir, temp, 300);
	free(temp);
	temp = ft_strjoin(data->exec_dir, data->cmd[0]);
	ft_strlcpy(data->exec_file, temp, 300);
	free(temp);
	return (0);
}

static	int		file_err(t_data *data, t_path_var *var)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(var->str, 2);
	ft_putstr_fd(": No such file or directory", 2);
	write(2, "\n", 1);
	g_t.status = 1;
	data->flag = 1;
	return (0);
}

int				get_exec_dir_file(t_data *data)
{
	t_path_var	var;

	var.idx = 0;
	var.flag = 0;
	if (NULL != (var.p = ft_strrchr(data->cmd[0], '/')))
		path_to_file(data, &var);
	while (data->paths[var.idx])
	{
		if (execfile_in_path(data, data->paths[var.idx]) == 1)
		{
			if (path_err(data, &var) == 1)
				return (0);
			break ;
		}
		var.idx++;
	}
	if (data->paths[var.idx] == NULL && var.flag == 1)
		return (file_err(data, &var));
	if (data->paths[var.idx] == NULL && var.flag == 0)
		return (0);
	return (1);
}
