#include "../minishell.h"

void	process_unset(t_data *data)
{
	if (data->cmd[1])
		delete_env(data, data->cmd[1]);
	get_paths(data);
	recover_std(data);
}
