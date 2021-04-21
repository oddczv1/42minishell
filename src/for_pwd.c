#include "../minishell.h"

void    process_pwd(t_data *data)
{
    char buf[1025];

    if (0 == getcwd(buf, 1024))
		ft_putstr_fd("err", 2);
	ft_putstr_fd(buf, 1);
	write(1, "\n", 2);
	recover_std(data);
}