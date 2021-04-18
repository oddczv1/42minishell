#include "../minishell.h"

void get_paths(t_data *data)
{
	char env_path[1000];
	int idx  = 0;
	while (data->env[idx])
	{
		if (ft_strncmp(data->env[idx], "PATH=", 5) == 0)
		{
			char *p = ft_strchr(data->env[idx], '=');
			//path = ft_strdup(p+1);
			ft_strlcpy(env_path, p + 1, 999);
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
    { 
        fprintf(stderr, "%s directory 정보를 읽을 수 없습니다.\n", path); 
        return -1; 
    }
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
	while (data->paths[idx])
	{
		if (execfile_in_path(data, data->paths[idx]) == 1)
		{
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
	if (data->paths[idx] == NULL)
	{
		//에러처리는 밑에 메인문에서 진행.
		return (0);
	}
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_data data;
	data.env = env;
	get_paths(&data);
	data.cmd = ft_split("bash", ' ');
	/*int idx = -1;
	while (data.paths[++idx])
		printf("split[%d] = %s\n", idx, data.paths[idx]);*/
	if (0 == get_exec_dir_file(&data))
	{
		printf("non found that execfile in any directory\n");
		exit(127);//이렇게 하는게 맞는데 아직 시그널 처리를 안해줌...
	}
	else//최종목표...!
	{
		printf("found that execfile in %s directory\n", data.exec_dir);
		printf("execfile is %s\n", data.exec_file);
	}
	return (0);
}