#include "../minishell.h"
#define TRUE 1
#define FALSE 0
void	recover_std(t_data *d)
{
	dup2(d->ft_std[0], 0);
	dup2(d->ft_std[1], 1);
}

void	process_builtin(t_data *data)//fork()사용하면 절대 안됨.
{
	char buf[1024];
	int idx;

	if (!ft_strncmp(data->cmd[0], "echo", 5))
	{
		idx = 1;
		if (data->cmd[1] == NULL)
		{
			write(1,"\n", 1);
			return ;
		}
		if (!ft_strncmp(data->cmd[idx], "-n", 3))
			idx++;
		while (data->cmd[idx + 1] && data->cmd[idx])
		{
			my_putstr_fd(data->cmd[idx], 1);//하나씩 write하다보니까 개행을 출력하지 못하는 문제가 발생. 따라서 my_putstr_fd 함수 생성.
			idx++;
			ft_putstr_fd(" ", 1);
		}
		if (ft_strncmp(data->cmd[1], "-n", 3) != 0)
		{
			my_putstr_fd(data->cmd[idx], 1);
			write(1, "\n", 2);
		}
		else//-n옵션 있을때 %개행처리? 이거 어떻게 하는건지..?
		{
			if (0 == fork())
			{
				my_putstr_fd(data->cmd[idx], 1);
			}
			else
				wait(NULL);
		}
		recover_std(data);
	}
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
	{
		if (0 == getcwd(buf, 1024))
			ft_putstr_fd("err", 1);
		ft_putstr_fd(buf, 1);
		write(1, "\n", 2);
		recover_std(data);
	}
	else if (!ft_strncmp(data->cmd[0], "env", 4))//getenv()함수 쓰면 절대 안됨.local에 저장된 env db사용한다고 생각하자.
	{
		if (data->cmd[1] == NULL)
		{
			idx = 0;
			while (data->env[idx])
			{
				ft_putstr_fd(data->env[idx], 1);
				ft_putstr_fd("\n", 1);
				idx++;
			}
		}
		else
		{
			if (-1 == findenv(data, buf))
				ft_putstr_fd("not found that env", 2);
			ft_putstr_fd(buf, 1);
		}
		recover_std(data);
	}
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
	{
		if (data->cmd[1] == NULL)
		{
			free(data->cmd[0]);
			data->cmd = ft_split("cd ~", ' ');
		}
		if (ft_strncmp(data->cmd[1], "~", 2) == 0)
		{
			int idx = 0;
			char buf[1000];
			while (data->env[idx])
    		{
        		if (match_key("HOME", data->env[idx]) == TRUE)
            		get_value(data->env[idx], buf);
				idx++;
			}
			if (data->env[idx] == NULL)
			{
				free(data->cmd[1]);
				data->cmd[1] = ft_strdup(buf);
			}
			else//혹시.. HOME 환경변수를 누군가 지워버렸다면....!
			{
				ft_putstr_fd("you can't have home!!!!!!!", 2);//원래 에러처리 안하고 그냥 엔터만 출력되는듯...
			}
		}
		if (-1 == chdir(data->cmd[1]))
		ft_putstr_fd("err", 2);
		recover_std(data);
	}
	else if (!ft_strncmp(data->cmd[0], "export", 7))//export만 입력하면 env와 동일하다.그렇게 바꿔야함.(정렬도 해주어야함.)
	{
		if (data->cmd[1])
			add_env(data, data->cmd[1]);
		recover_std(data);
	}
	else if (!ft_strncmp(data->cmd[0], "unset", 6))
	{
		if (data->cmd[1])
			delete_env(data, data->cmd[1]);
		else
		{
			ft_putstr_fd("unset: not enough arguments", 2);
			write(1, "\n", 1);
		}
		recover_std(data);
	}
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
	{
		//terminate shell program
		recover_std(data);
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

int		is_exec_usr(t_data *data)
{
	DIR *dir_ptr = NULL; 
    struct dirent *file = NULL; 
    char dir[1024];
	int ret = 0;
	int size= ft_strlen(data->cmd[0]);
    strncpy(dir, "/usr/bin/", sizeof(dir));
    if((dir_ptr = opendir(dir)) == NULL) 
    { 
        fprintf(stderr, "%s directory 정보를 읽을 수 없습니다.\n", dir); 
        return -1; 
    }
    while((file = readdir(dir_ptr)) != NULL)
    {
		if (!ft_strncmp(file->d_name, data->cmd[0], size + 1) && (int)ft_strlen(file->d_name) == size)
		{
			ret = 1;
			break;
		}
    }
    closedir(dir_ptr);
    return ret; 
}

int		is_exec_bin(t_data *data)
{
	DIR *dir_ptr = NULL; 
    struct dirent *file = NULL; 
    char dir[1024];
	int ret = 0;
	int size= ft_strlen(data->cmd[0]);
    strncpy(dir, "/bin/", sizeof(dir));
    if((dir_ptr = opendir(dir)) == NULL) 
    { 
        fprintf(stderr, "%s directory 정보를 읽을 수 없습니다.\n", dir); 
        return -1; 
    }
    while((file = readdir(dir_ptr)) != NULL) 
    {
		if (!ft_strncmp(file->d_name, data->cmd[0], size + 1) && (int)ft_strlen(file->d_name) == size)
		{
			ret = 1;
			break;
		}
    }
    closedir(dir_ptr);
    return ret; 
}

void	process_bin_exec(t_data *data)
{
	int status;
	pid_t pid;
	char *execfile = ft_strjoin("/bin/", data->cmd[0]);
	if ((pid = fork()) == 0)
		execve(execfile, data->cmd, NULL);
	else
		waitpid(pid, &status, 0);
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
	}
	recover_std(data);
	return ;
}

int		is_builtin(t_data *data)
{
	if (!ft_strncmp(data->cmd[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "env", 4))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "export", 7))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
		return (1);
	else
		return (0);
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
	}
}

void allocat_cmd(t_data *data, char **arg)
{
	int size = 1;
	while (arg[size])
		size++;
	data->cmd = malloc(sizeof(char *) * (size + 1));
	int idx = 1;
	while (arg[idx])
	{
		data->cmd[idx - 1] = ft_strdup(arg[idx]);
		idx++;
	}
	data->cmd[size] = NULL;
}

void allocat_env(t_data *data, char **env)
{
	int size = 0;
	while (env[size])
		size++;
	data->env = malloc(sizeof(char *) * (size + 1));
	int idx = 0;
	while (env[idx])
	{
		data->env[idx] = ft_strdup(env[idx]);
		idx++;
	}
	data->env[size] = NULL;
}