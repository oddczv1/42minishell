#include "../minishell.h"
#define CUR(X) ((X % 2) * (2))//idx짝수->0, idx홀수->2

void	single_builtin(t_data *d, int *fx, int fd, int idx)
{
	dup2(fx[CUR(idx) + 1], 1);
	process_builtin(d);
	close(fd);
	close(fx[CUR(idx) + 1]);
}

void	err_messag(t_data *d, int *fx, int fd, int idx)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(d->cmd[0], 2);
	ft_putstr_fd(": command not found", 2);
	write(2, "\n", 1);
	close(fx[CUR(idx)]);
	close(fx[CUR(idx) + 1]);
	close(fd);
}

void	ready_for_execute(int *fx, int fd, int idx)
{
	dup2(fd, 0);
	dup2(fx[CUR(idx) + 1], 1);
	close(fd);
	close(fx[CUR(idx)]);
	close(fx[CUR(idx) + 1]);
}

int		pipe_func(t_data *d, int *fx, int fd, int idx)
{
	pipe(&fx[CUR(idx)]);
	if (is_builtin(d))
		single_builtin(d, fx, fd, idx);
	else if (get_exec_dir_file(d))
	{
		if (0 == (d->pids[idx] = fork()))
		{
			ready_for_execute(fx, fd, idx);
			execve(d->exec_file, d->cmd, d->env);
		}
		else
		{
			if (idx != 0)//제일 초기단계만 아니면 이 조건문에서 참이됨.
				close(fd);
		}
	}
    else if (!d->flag)
	{
		err_messag(d, fx, fd, idx);
		return (d->ft_std[0]);//여기서 status값 갱신하지 않고 다른데에서 갱신
	}
 	close(fx[CUR(idx) + 1]);
	if (idx != 0)//제일 초기단계만 아니면 이 조건문에서 참이됨.
		close(fd);
	return (fx[CUR(idx)]);
}

int	err_message(t_data *d)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(d->cmd[0], 2);
	ft_putstr_fd(": command not found", 2);
	write(2, "\n", 1);
	exit(127);
}

void	connect_pipe(t_data *d, int *idx, int *fx, int *fd)
{
	*idx = 0;
	*fd = dup(0);
	while (d->argv[*idx + 1] != NULL)
    {
        ft_check_split(d, *idx);
        *fd = pipe_func(d, fx, *fd, *idx);
        ft_free(d->cmd);
        (*idx)++;
    }
}

void	last_command(t_data *d, int *fd, int *fx, int *idx)
{
	ft_check_split(d, *idx);
	dup2(*fd, 0);
	close(*fd);
	close(fx[CUR(*idx-1)]);
	if (d->enable != 0)
		exit(g_t.status);
	if (is_builtin(d))
		process_builtin(d);//status값의 갱신작업은 process_builtin 함수에서 진행. status=0으로 초기화되어있음을 기억...
	else if (get_exec_dir_file(d))
		execve(d->exec_file, d->cmd, d->env);//얘안에 exit(code)가 들어있음.. (think.c 의 모든함수는 exit(code)로 끝나야함.)
	else if (!d->flag)
		err_message(d);
	else if (g_t.status)//get_exec_dir_file에서 경로가 틀렸을때의 경우
		exit(g_t.status);
}

void    process_pipe(t_data *d)//recover_std함수 호출 필요없을듯.... 독립이니까
{
    int fd;
    int idx;
    int fx[4];
	int count;
	int temp_status;

	connect_pipe(d, &idx, fx, &fd);
    if (0 == (d->pids[idx] = fork()))
		last_command(d, &fd, fx, &idx);
	count = idx;
	while (count >= 0)
	{
		waitpid(d->pids[count], &temp_status, 0);//여기서 반환된 상태값은 사용 안 될 예정 (마지막 명령어의 상태값이 중요함.)
		if (count == (idx))
			g_t.status = WEXITSTATUS(temp_status);
		count--;
	}
	exit(g_t.status);
}
