#include "../minishell.h"

void    process_export(t_data *data)
{
    if (data->cmd[1])
		add_env(data, data->cmd[1]);
	recover_std(data);
}