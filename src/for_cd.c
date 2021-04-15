#include "../minishell.h"

void    process_cd(t_data *data)
{
    int idx = 0;
    char buf[1025];

    if (data->cmd[1] == NULL)
	{
		free(data->cmd[0]);
		data->cmd = ft_split("cd ~", ' ');
	}
	if (ft_strncmp(data->cmd[1], "~", 2) == 0)//이상하게도 ..이랑 /는 인식을 잘 하더라. 유독 ~ 만 인식을 잘 못함. 
	{
		while (data->env[idx])
    	{
      		if (match_key("HOME", data->env[idx++]) == TRUE)
           		get_value(data->env[idx - 1], buf);
		}
		free(data->cmd[1]);
		data->cmd[1] = ft_strdup(buf);
	}
	if (-1 == chdir(data->cmd[1]))
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		write(2, data->cmd[1], ft_strlen(data->cmd[1]));
		write(2, "\n", 1);
	}
	recover_std(data);//process함수 제일 마지막에서 일괄적으로 처리해도 되는데 일단은 각각의 처리함수에 넣어두자(시그널이 걸려서..)
}