#include "../minishell.h"

int		is_exec_usr(t_data *data)
{
	DIR *dir_ptr = NULL; 
    struct dirent *file = NULL; 
    char dir[1024];
	int ret = 0;
	int size= ft_strlen(data->cmd[0]);
    strncpy(dir, "/usr/bin/", sizeof(dir));
    if((dir_ptr = opendir(dir)) == NULL) 
    { 
        fprintf(stderr, "%s directory 정보를 읽을 수 없습니다.\n", dir); 
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

int		is_exec_bin(t_data *data)
{
	DIR *dir_ptr = NULL; 
    struct dirent *file = NULL; 
    char dir[1024];
	int ret = 0;
	int size= ft_strlen(data->cmd[0]);
    strncpy(dir, "/bin/", sizeof(dir));
    if((dir_ptr = opendir(dir)) == NULL) 
    { 
        fprintf(stderr, "%s directory 정보를 읽을 수 없습니다.\n", dir); 
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

int		is_builtin(t_data *data)
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
	else
		return (0);
}
