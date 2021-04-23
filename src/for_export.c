#include "../minishell.h"

/*int		is_valid(char *str)
{
	int idx = 0;

	while (str[idx] && str[idx] != '=')
	{
		if (ft_isalpha(str[idx]) == 0)
			return (0);
		idx++;
	}
	return (1);
}*/

int		add_operation(char *str)
{
	char	*p;

	p = ft_strchr(str, '=');
	if (*(p - 1) == '+')
		return (1);
	else
		return (0);
}

int		check_head_valid(t_data *data)
{
	char head;

	head = data->cmd[1][0];
	if (ft_isalpha(head) || head == '_')
		return (1);
	else
		return (0);
}

int		is_valid_char(char ch)
{
	if (ft_isdigit(ch))
		return (1);
	else if (ft_isalpha(ch))
		return (1);
	else if (ch == '_' || ch == '+')
		return (1);
	else
		return (0);
}

int		check_other_valid(t_data *data)
{
	int		idx;
	//char	buf[300];

	idx = 0;
	while (data->cmd[1][idx] && data->cmd[1][idx] != '=')
	{
		if (is_valid_char(data->cmd[1][idx]))
			idx++;
		else
			return (0);
	}
	return (1);
}

int		is_valid(t_data *data)
{
	if (!check_head_valid(data))
		return (0);
	else if (!check_other_valid(data))
		return (0);
	else
		return (1);
}

void	process_print(t_data *data)
{
    int idx;
    char *p;
    if (data->cmd[1] == NULL)
    {
        idx = 0;
        while (data->env[idx])
        {
            ft_putstr_fd("declare -x ", 1);
            int count = 0;
            while (data->env[idx][count])
            {
                write(1, &data->env[idx][count], 1);
                if (data->env[idx][count] == '=')
                    break;
                count++;
            }
            if ((p = ft_strchr(data->env[idx], '=')) != NULL)
            {
                write(1, "\"", 1);
                ft_putstr_fd(p+1, 1);
                write(1, "\"", 1);
                ft_putstr_fd("\n", 1);
            }
            idx++;
        }
    }
    recover_std(data);
}
void    process_export(t_data *data)
{
    if (data->cmd[1] && is_valid(data))
        add_env(data, data->cmd[1]);
    else if (!data->cmd[1])
        process_print(data);
	else
	{
		ft_putstr_fd("bash: export: `", 2);
        ft_putstr_fd(data->cmd[1], 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
		data->flag = 1;
		g_t.status = 1;
	}
    get_paths(data);
    recover_std(data);
}
