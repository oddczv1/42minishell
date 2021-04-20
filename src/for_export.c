#include "../minishell.h"


void    process_print(t_data *data)
{
    int idx;
    //char buf[1025];
	//char *temp;
	char *p;
    if (data->cmd[1] == NULL)
	{
		idx = 0;
		while (data->env[idx])
		{
			ft_putstr_fd("declare -x ", 1);
			int count = 0;
			while (data->env[idx][count])
			{
				write(1, &data->env[idx][count], 1);
				if (data->env[idx][count] == '=')
					break;
				count++;
			}
			if ((p = ft_strchr(data->env[idx], '=')) != NULL)
			{
				write(1, "\"", 1);
				ft_putstr_fd(p+1, 1);
				write(1, "\"", 1);
				ft_putstr_fd("\n", 1);
			}
			idx++;
		}
	}
	recover_std(data);
}

void    process_export(t_data *data)
{
    if (data->cmd[1])
		add_env(data, data->cmd[1]);
	else
		process_print(data);
	get_paths(data);
	recover_std(data);
}