/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_exec_dir_file_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:07:09 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/24 15:07:10 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_paths(t_data *data)
{
	char	env_path[1000];
	int		idx;
	char	*p;

	idx = 0;
	while (data->env[idx])
	{
		if (ft_strncmp(data->env[idx], "PATH=", 5) == 0)
		{
			p = ft_strchr(data->env[idx], '=');
			ft_strlcpy(env_path, p + 1, 1000);
		}
		idx++;
	}
	data->paths = ft_split(env_path, ':');
}

int		execfile_in_path(t_data *data, char *path)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	int				ret;
	int				size;

	dir_ptr = NULL;
	file = NULL;
	ret = 0;
	size = ft_strlen(data->cmd[0]);
	if ((dir_ptr = opendir(path)) == NULL)
		return (0);
	while (((file = readdir(dir_ptr)) != NULL) && !ret)
	{
		if (!ft_strncmp(file->d_name, data->cmd[0], size + 1) && \
			(int)ft_strlen(file->d_name) == size)
			ret = 1;
	}
	closedir(dir_ptr);
	return (ret);
}
