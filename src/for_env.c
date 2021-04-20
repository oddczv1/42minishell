#include "../minishell.h"
#define TRUE 1
#define FALSE 0

void    over_write(t_data *data, char *key_value, int idx)
{
    free(data->env[idx]);
    data->env[idx] = ft_strdup(key_value);
}

int     match_key(char *key_value, char *str)//검증필요
{
    int size = 0;
    while (key_value[size] != 0 && key_value[size] != '=')
        size++;
    if (!ft_strncmp(key_value, str, size - 1) && (str[size] == '=' || str[size] == '\0'))
        return (TRUE);
    return (FALSE);
}

/*                                               */
/*                                               */
/*                                               */
/*                                               */

void    get_value(char *str, char *buf)
{
    //int idx = 0;
    char *p;
    p = ft_strchr(str, '=');
    ft_strlcpy(buf, p + 1, 1024);
}

int     findenv(t_data *data, char *buf)
{
    int idx = 0;
    //char *str;
    char *key = data->cmd[1];
    while (data->env[idx])
    {
        if (match_key(key, data->env[idx]) == TRUE)
        {
            get_value(data->env[idx], buf);
            return (1);
        }
    }
    return (-1);
}

void    renewer_env(t_data *data, char *key, char *str, int size)
{
    char **new_env = malloc(sizeof(char *) * size);
    new_env[size - 1] = NULL;
    int idx = 0;
    int count = 0;
    if (str == NULL)
    {//delete one env
        while (data->env[idx])
        {
            if (match_key(key, data->env[idx]) == TRUE)
            {//not copy
                free(data->env[idx]);
                idx++;
            }
            else//copy
                new_env[count++] = data->env[idx++];
        }//삭제하려는 키가 현재의 env에 존재하지 않을때 딱히 err처리를 해주지 않는다.
        new_env[count] = NULL;//size == count?
    }
    else
    {//add one env
        while (data->env[idx])
            new_env[count++] = data->env[idx++];
        new_env[count++] = ft_strdup(str);
        new_env[count] = NULL;//size == count?
    }
    free(data->env);
    data->env = new_env;
}

int    delete_env(t_data *data, char *key)
{
    int idx = 0;
    while (data->env[idx])
        idx++;
    renewer_env(data, key, NULL, idx + 1 - 1);
    return (1);
}

int     add_env(t_data *data, char *key_value)
{
    int idx = 0;
    while (data->env[idx] && ft_strchr(data->cmd[1], '='))//종료조건
    {
        if (match_key(key_value, data->env[idx]) == TRUE)
        {
            over_write(data, key_value, idx);//덮어쓰기를 진행.
            break;
        }
        idx++;
    }
    //renewer_env(data->env, NULL, data->cmd[1], idx + 1 + 1);//이게 더 나을수도...?
    if (data->env[idx] == NULL && ft_strchr(data->cmd[1], '='))//루프 종료조건 이용한 조건문(덮어쓰기 했으면 아래 함수 실행 안함)
        renewer_env(data, key_value, data->cmd[1], idx + 1 + 1);
    return (1);
}

void    process_env(t_data *data)
{
    int idx;
    //char buf[1025];

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
	/*else
	{
		if (-1 == findenv(data, buf))
			ft_putstr_fd("not found that env", 2);
		ft_putstr_fd(buf, 1);
	}*///이런 케이스 들어오면 안됨.. 멘데토리에 명시..
	recover_std(data);
}
