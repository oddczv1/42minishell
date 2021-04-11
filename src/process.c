#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>//for wait function
#include "minishell.h"
int check_apos(char *str);
void	process_builtin(t_data *data)//fork()사용하면 절대 안됨.
{
	char buf[1024];
	int idx;

	if (!ft_strncmp(data->cmd[0], "echo", 5))
	{
		//write() printf() getenv()
		idx = 1;
		if (!ft_strncmp(dat->cmd[idx], "-n", 3))
		{
			delete_last_newline(data->cmd)
			idx++;
		}
		while (cmd[idx])
		{
			ft_putstr_fd(cmd[0] + check_apos(cmd[0]), 1);//표준출력 리다이렉션은 영리치님의 몫인데, 명령어가 표준입력 리다이렉션이면?
			idx++;
		}
	}
	else if (!ft_strncmp(data.cmd[0], "pwd", 4))
	{
		if (0 == getcwd(buf, 1024))
			ft_putstr_fd("err", 1);
		ft_putstr_fd(buf, 1);//표준출력 디라이렉션 처리는 영리치님의 몫임.
	}
	else if (!ft_strncmp(data.cmd[0], "env", 4))//getenv()함수 쓰면 절대 안됨.
	{
		if (-1 == findenv(data, buf))
			ft_putstr_fd("not found that env", 1);
		ft_putstr_fd(buf, 1);//표준출력 디라이렉션 처리는 영리치님의 몫임.
	}//dup로 표준입력 출력 다른걸로 변경해주신걸 내가 사용하는데, 사용이후 원래값으로 변경해주는 작업이 필요. 이작업도 영리치님이...
	else if (!ft_strncmp(data.cmd[0], "cd", 3))
	{
		if (-1 == chdir(data.cmd[1]))
			ft_putstr_fd("err", 1);
	}
	else if (!ft_strncmp(data.cmd[0], "export", 7))
	{
		add_env(data, data.cmd[1])
	}
	else if (!ft_strncmp(data.cmd[0], "unset", 6))
	{
		delete_env(data, data,cmd[1])
	}
	else if (!ft_strncmp(data.cmd[0], "exit", 5))
	{
		//terminate shtell program
	}
	else if (!ft_strncmp(data.cmd[0], "bash", 5))
	{
		//아직 미정임
	}
	else 
		ft_putstr_fd("error", 1);
}



void	process_bin(t_data *p_data)//이 부분 내일 geek for geek 보면서 공부.
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
}