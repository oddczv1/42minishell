#include "../minishell.h"

static	void	path_to_file(t_data *data, t_path_var *var)
{
	var->flag = 1;
	ft_strlcpy(var->str, data->cmd[0], 300);
	*(var->p) = 0;
	ft_strlcpy(var->temp_dir, data->cmd[0], 300);
	var->temp_file = ft_strdup(var->p+ 1);
	free(data->cmd[0]);
	data->cmd[0] = var->temp_file;
}

static	int		path_err(t_data *data, t_path_var *var)
{
	char *temp;

	if (var->flag == 1 && ft_strncmp(var->temp_dir, data->paths[var->idx], 300))
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

int get_exec_dir_file(t_data *data)
{
	t_path_var var;

	var.idx = 0;
	var.flag = 0;
	if (NULL != (var.p = ft_strrchr(data->cmd[0], '/')))
		path_to_file(data, &var);
	while (data->paths[var.idx])
	{
		if (execfile_in_path(data, data->paths[var.idx]) == 1)//경로형식이고 실행파일은 실제로 존재하는 파일이지만 경로자체가 틀린경우
		{
			if (path_err(data, &var) == 1)
				return (0);
			/*if (flag == 1 && ft_strncmp(temp_dir, data->paths[idx], 300))
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd(": No such file or directory", 2);
				write(2, "\n", 1);
				g_g_t.status = 1;
				data->flag = 1;
				return 0;
			}
			ft_strlcpy(data->exec_dir, data->paths[idx], 300);
			char *temp = ft_strjoin(data->exec_dir, "/");
			ft_strlcpy(data->exec_dir, temp, 300);
			free(temp);
			temp = ft_strjoin(data->exec_dir, data->cmd[0]);
			ft_strlcpy(data->exec_file, temp, 300);
			free(temp);*/
			break;
		}
		var.idx++;
	}
	if (data->paths[var.idx] == NULL && var.flag == 1)//경로형식을 전제로 하여... 경로가 틀렸거나 실행파일 자체가 틀린경우
		return (file_err(data, &var));
	if (data->paths[var.idx] == NULL && var.flag == 0)
		return (0);//에러처리는 이 함수의 반환값을 받는 함수에서 진행.
	return (1);
}
