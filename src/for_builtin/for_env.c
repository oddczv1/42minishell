#include "../minishell.h"

int     match_key(char *key_value, char *str)//검증필요
{
    int size = 0;
    while (key_value[size] != 0 && key_value[size] != '=')
        size++;
    if (!ft_strncmp(key, str, size - 1) && (str[size] == '=' || str[size] == '\0'))
        return (TRUE);
    return (FALSE);
}

/*                                               */
/*                                               */
/*                                               */
/*                                               */

void    get_value(char *str, char *buf)
{
    int idx = 0;
    char *p;
    p = ft_strchr(str, '=');
    ft_strcpy(buf, p + 1);
}

int     findenv(t_data *data, char *buf)
{
    int idx = 0;
    char *str;
    char *key = data->cmd[1];
    while (data->env[idx])
    {
        if (match_key(key, data->env[idx] == TRUE)
        {
            get_value(data->env[idx], buf);
            return (1);
        }
    }
    return (-1)
}

void    renewer_env(char **env, char *key, char *str, int size)
{
    new_env = malloc(sizeof(char *) * size);
    new_env[size - 1] = NULL;
    int idx = 0;
    int count = 0;
    if (str == NULL)
    {//delete one env
        while (env[idx])
        {
            if (match_key(key, env[idx]) == TRUE)
            {//not copy
                free(env[idx]);
                idx++;
            }
            else//copy
                new_env[count++] = env[idx++];
        }
        new_env[count] = NULL;//size == count?
    }
    else
    {//add one env
        while (data->env[idx])
            new_env[count++] = env[idx++];
        new_env[count++] = ft_strdup(str);
        new_env[count] = NULL;//size == count?
    }
    free(env);
}

int    delete_env(t_data *data, char *key)
{
    int idx = 0;
    while (data->env[idx])
        idx++;
    renewer_env(data->env, key, NULL, idx + 1 - 1);
    return (1)
}

int     add_env(t_data *data, char *key_value)
{
    int idx = 0;
    while (data->env[idx])
    {
        if (match_key(key_value, data->env[idx]) == TRUE)
        {
            ft_putstr_fd("the key already exist", 1);
            return (-1);
        }
    }
    //renewer_env(data->env, NULL, data->cmd[1], idx + 1 + 1);//이게 더 나을수도...?
    renewer_env(data->env, key_value, data->cmd[1], idx + 1 + 1);
    return (1);
}