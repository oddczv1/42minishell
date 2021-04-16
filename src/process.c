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
		//terminate shell program
		exit(0);//이거만 해주면 되나...? 
		recover_std(data);//필요없을듯..?
	}
	else if (!ft_strncmp(data->cmd[0], "bash", 5))
	{
		//아직 미정임
		recover_std(data);
	}
	else 
	{
		ft_putstr_fd("error11", 2);
		recover_std(data);
	}
}

void	process_bin_exec(t_data *data)
{
	int status;
	pid_t pid;
	char *execfile = ft_strjoin("/bin/", data->cmd[0]);
	if ((pid = fork()) == 0)
		execve(execfile, data->cmd, NULL);//자식프로세스에서는 메모리해제 안해줘도 될거라고 판단했는데, 생각해보면 해줘야하는거 같기도..?
	else
	{
		waitpid(pid, &status, 0);
		free(execfile);
	}
	recover_std(data);
	return ;
}

void	process_usr_exec(t_data *data)
{
	int status;
	pid_t pid;
	char *execfile = ft_strjoin("/usr/bin/", data->cmd[0]);
	if ((pid = fork()) == 0)
	{
		execve(execfile, data->cmd, NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(execfile);
	}
	recover_std(data);
	return ;
}

void	process(t_data *data)
{
	if (is_builtin(data))
	{
		process_builtin(data);
	}
	else if (is_exec_usr(data))
	{
		process_usr_exec(data);
	}
	else if (is_exec_bin(data))
	{
		process_bin_exec(data);
	}
	else
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		write(2, data->cmd[0], ft_strlen(data->cmd[0]));
		write(1, "\n", 1);
		if (0 == fork())
			exit(127);
		else
			wait(NULL);
	}
}
