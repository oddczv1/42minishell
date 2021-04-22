#include "../minishell.h"

void	process_export(t_data *data)
{
	if (data->cmd[1])
		add_env(data, data->cmd[1]);
	else
		process_env(data);
	get_paths(data);
	recover_std(data);
}
