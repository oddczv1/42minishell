#include "../minishell.h"

void    process_bash(t_data *data)
{
    if (fork() == 0)
	    execve("/bin/bash", data->cmd, data->env);
	else
		wait(NULL);
	recover_std(data);
}