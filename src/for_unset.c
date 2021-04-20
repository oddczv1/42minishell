#include "../minishell.h"

void    process_unset(t_data *data)
{
    if (data->cmd[1])
		delete_env(data, data->cmd[1]);
	else
	{
		//ft_putstr_fd("unset: not enough arguments", 2);//배쉬에서는 이부분이 없음.
		//write(1, "\n", 1);
	}
	get_paths(data);
	recover_std(data);
}