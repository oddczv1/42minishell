#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>//for wait function
#include "../minishell.h"
void	delete_last_newline(char **cmd);
int     match_key(char *key_value, char *str);
void    get_value(char *str, char *buf);
int     findenv(t_data *data, char *buf);
void    renewer_env(char **env, char *key, char *str, int size);
int    delete_env(t_data *data, char *key);
int     add_env(t_data *data, char *key_value);
int		is_newline(char *str);
void	my_putstr_fd(char *str, int fd);
void	process_builtin(t_data *data)//fork()사용하면 절대 안됨.
{
	char buf[1024];
	int idx;

	if (!ft_strncmp(data->cmd[0], "echo", 5))
	{
		//write() printf() getenv()
		idx = 1;
		if (!ft_strncmp(data->cmd[idx], "-n", 3))
			idx++;
		while (data->cmd[idx])
		{
			my_putstr_fd(data->cmd[idx], 1);//하나씩 write하다보니까 개행을 출력하지 못하는 문제가 발생.
			idx++;
			if (data->cmd[idx])
				ft_putstr_fd(" ", 1);
		}
		if (ft_strncmp(data->cmd[1], "-n", 3) != 0)
			write(1, "\n", 2);
	}
	else if (!ft_strncmp(data->cmd[0], "pwd", 4))
	{
		if (0 == getcwd(buf, 1024))
			ft_putstr_fd("err", 1);
		ft_putstr_fd(buf, 1);//표준출력 디라이렉션 처리는 영리치님의 몫임.
	}
	else if (!ft_strncmp(data->cmd[0], "env", 4))//getenv()함수 쓰면 절대 안됨.
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
		else if (-1 == findenv(data, buf))
			ft_putstr_fd("not found that env", 1);
		ft_putstr_fd(buf, 1);//표준출력 디라이렉션 처리는 영리치님의 몫임.
	}//dup로 표준입력 출력 다른걸로 변경해주신걸 내가 사용하는데, 사용이후 원래값으로 변경해주는 작업이 필요. 이작업도 영리치님이...
	else if (!ft_strncmp(data->cmd[0], "cd", 3))
	{
		if (-1 == chdir(data->cmd[1]))
			ft_putstr_fd("err", 1);
	}
	else if (!ft_strncmp(data->cmd[0], "export", 7))
	{
		add_env(data, data->cmd[1]);
	}
	else if (!ft_strncmp(data->cmd[0], "unset", 6))
	{
		delete_env(data, data->cmd[1]);
	}
	else if (!ft_strncmp(data->cmd[0], "exit", 5))
	{
		//terminate shell program
	}
	else if (!ft_strncmp(data->cmd[0], "bash", 5))
	{
		//아직 미정임
	}
	else 
		ft_putstr_fd("error", 1);
}

/*void	process_bin(t_data *p_data)//이 부분 내일 geek for geek 보면서 공부.
{
	int status;
	pid_t pid;
	int fd[4];

	pipe(fd);
	if ((pid = fork()) == 0)
	{
		execve("/bin/bash", cmd, NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return ;
}*/

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

int main(int argc, char *argv[], char *env[])
{
	t_data data;
	allocat_cmd(&data, argv);
	//data.cmd = ft_split("echo test\n", ' ');
	process_builtin(&data);
	/*data.cmd = ft_split("export test=testing", ' ');
	allocat_env(&data, env);
	process_builtin(&data);
	data.cmd = ft_split("export HOME=second", ' ');
	process_builtin(&data);
	int idx = 0;
	while (data.env[idx])
		printf("%s\n", data.env[idx++]);*/
	
	/*allocat_env(&data, env);
	data.cmd = ft_split("export test=test", ' ');
	process_builtin(&data);
	data.cmd = ft_split("unset nononono", ' ');
	process_builtin(&data);
	int idx = 0;
	//while (data.env[idx])
		//printf("%s\n", data.env[idx++]);*/
	return (0);
}