#include "../minishell.h"

void	get_paths(t_data *data)
{
	char env_path[1000];
	int idx= 0;
	while (data->env[idx])
	{
		if (ft_strncmp(data->env[idx], "PATH=", 5) == 0)
		{
			char *p = ft_strchr(data->env[idx], '=');
			ft_strlcpy(env_path, p + 1, 1000);
		}
		idx++;
	}
	data->paths = ft_split(env_path, ':');
}

int	execfile_in_path(t_data *data, char *path)
{
	DIR *dir_ptr = NULL; 
    struct dirent *file = NULL; 
	int ret = 0;
	int size= ft_strlen(data->cmd[0]);
	if((dir_ptr = opendir(path)) == NULL) 
		return 0;//return 0 이 맞을듯...? 
	while((file = readdir(dir_ptr)) != NULL)
	{
		if (!ft_strncmp(file->d_name, data->cmd[0], size + 1) && (int)ft_strlen(file->d_name) == size)
		{
			ret = 1;
			break;
		}
	}
	closedir(dir_ptr);
	return ret; 
}

int get_exec_dir_file(t_data *data)
{
	int idx = 0;
	char str[300];
	char temp_dir[300];
	char *temp_file;
	char *p;
	int	flag = 0;
	if (NULL != (p = ft_strrchr(data->cmd[0], '/')))
	{
		flag = 1;
		ft_strlcpy(str, data->cmd[0], 300);
		*p = 0;
		ft_strlcpy(temp_dir, data->cmd[0], 300);
		temp_file = ft_strdup(p+ 1);
		free(data->cmd[0]);
		data->cmd[0] = temp_file;
	}
	while (data->paths[idx])
	{
		if (execfile_in_path(data, data->paths[idx]) == 1)//경로형식이고 실행파일은 실제로 존재하는 파일이지만 경로자체가 틀린경우
		{
			if (flag == 1 && ft_strncmp(temp_dir, data->paths[idx], 300))
			{
				ft_putstr_fd("zsh: no such file or directory: ", 2);
				ft_putstr_fd(str, 2);
				write(2, "\n", 1);
				data->status = 1;
				data->flag = 1;
				return 0;
			}
			ft_strlcpy(data->exec_dir, data->paths[idx], 300);
			char *temp = ft_strjoin(data->exec_dir, "/");
			ft_strlcpy(data->exec_dir, temp, 300);
			free(temp);
			temp = ft_strjoin(data->exec_dir, data->cmd[0]);
			ft_strlcpy(data->exec_file, temp, 300);
			free(temp);
			break;
		}
		idx++;
	}
	if (data->paths[idx] == NULL && flag == 1)//경로형식을 전제로 하여... 경로가 틀렸거나 실행파일 자체가 틀린경우
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		write(2, "\n", 1);
		data->status = 1;
		return 0;
	}
	if (data->paths[idx] == NULL && flag == 0)
	{
		//에러처리는 이 함수의 반환값을 받는 함수에서 진행.
		return (0);
	}
	return (1);
}
