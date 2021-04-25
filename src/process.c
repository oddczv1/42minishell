/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:03:40 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/25 12:54:27 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	recover_std(t_data *d)
{
	dup2(d->ft_std[0], 0);
	dup2(d->ft_std[1], 1);
}

void	process_builtin(t_data *data)
{
	if (!ft_strncmp(data->cmd[0], "echo", 5))
		porcess_echo(data);
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
		process_pwd(data);
	else if (!ft_strncmp(data->cmd[0], "env", 4))
		process_env(data);
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
		process_cd(data);
	else if (!ft_strncmp(data->cmd[0], "export", 7))
		process_export(data);
	else if (!ft_strncmp(data->cmd[0], "unset", 6))
		process_unset(data);
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
		exit(0);
	else
		process_bash(data);
	if (!data->flag)
		g_t.status = 0;
}

void	process_exec(t_data *data)
{
	int		status;
	pid_t	pid;

	if ((pid = fork()) == 0)
		execve(data->exec_file, data->cmd, data->env);
	else
	{
		g_t.pids = pid;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_t.status = WEXITSTATUS(status);
		if (status == 2)
			g_t.status = 130;
		if (status == 3)
			g_t.status = 131;
	}
	recover_std(data);
	return ;
}

void	process(t_data *data)
{
	if (is_builtin(data))
		process_builtin(data);
	else if (get_exec_dir_file(data))
		process_exec(data);
	else if (!data->flag)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(data->cmd[0], 2);
		ft_putstr_fd(": command not found", 2);
		write(2, "\n", 1);
		g_t.status = 127;
	}
	recover_std(data);
}
