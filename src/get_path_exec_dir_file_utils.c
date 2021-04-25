/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_exec_dir_file_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:07:09 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/25 19:31:12 by huchoi           ###   ########.fr       */
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
	if (data->paths != NULL)
	{
		idx = 0;
		while (data->paths[idx])
			free(data->paths[idx++]);
		free(data->paths);
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

int		ft_relative_path_check(t_data *data, t_path_var *var)
{
	//ft_putstr_fd("reach???\n", 2);
	char	original[1024];
	char	*test;
	char	abs_path[1024];
	int		ret;

	test = getcwd(original, 1024);
	printf("original : %s\n", original);
	printf("original : %s\n", test);
	int num = chdir(var->temp_dir);
	printf("num = %d\n", num);
	printf("var->temp_dir = %s\n", var->temp_dir);
	getcwd(abs_path, 1024);
	printf("abs_path = %s\n", abs_path);
	if (ft_strncmp(abs_path, data->paths[var->idx], 1024) == 0)//일치하면
		ret = 1;
	else if (ft_strncmp(var->temp_dir, data->paths[var->idx], 300) == 0)
		ret = 1;
	else//일치하지않으면
		ret = 0;
	ft_putchar_fd(ret + '0', 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(abs_path, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(data->paths[var->idx], 2);
	chdir(original);//절대 지우면 안됨.
	printf("original : %s\n", original);
	return (ret);
}
