#include "../minishell.h"

void	recover_std(t_data *d)
{
	dup2(d->ft_std[0], 0);
	dup2(d->ft_std[1], 1);
}

void	process_builtin(t_data *data)//빌트인은 어떤경우에서라도 fork()사용하면 절대 안됨.
{
	if (!ft_strncmp(data->cmd[0], "echo", 5))
		porcess_echo(data);
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
		process_pwd(data);
	else if (!ft_strncmp(data->cmd[0], "env", 4))//getenv()함수 쓰면 절대 안됨.local에 저장된 env db사용한다고 생각하자.
		process_env(data);
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
		process_cd(data);
	else if (!ft_strncmp(data->cmd[0], "export", 7))//export만 입력하면 env와 동일하다.그렇게 바꿔야함.(정렬도 해주어야함.)
		process_export(data);
	else if (!ft_strncmp(data->cmd[0], "unset", 6))
		process_unset(data);
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
	{
		exit(0);//이거만 해주면 되나...? 
		recover_std(data);//필요없을듯..?
	}
	else //bash임.
	{
		if (fork() == 0)
			execve("/bin/bash", data->cmd, NULL);
		else
			wait(NULL);
		recover_std(data);
	}
}

void	process_exec(t_data *data)
{
	int status;
	pid_t pid;
	if ((pid = fork()) == 0)
		execve(data->exec_file, data->cmd, NULL);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
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
	else
	{
		//error
		ft_putstr_fd("zsh: command not found: ", 2);
		write(2, data->cmd[0], ft_strlen(data->cmd[0]));
		write(2, "\n", 1);
		/*if (0 == fork())
		{
			data->status = 127;
			exit(127);
		}
		else
			wait(NULL);*/
		data->status = 127;
	}
	recover_std(data);
}
