#include "../minishell.h"

int main(int argc, char **argv, char **env)
{
	char **cmd = ft_split("ls -al", ' ');
	char path[1000];
	int idx = 0;
	while (env[idx])
	{
		if (ft_strncmp("PATH=", env[idx], 5))
		{
			char *p = ft_strchr(env[idx], '=');
			ft_strlcpy(path, p+1, ft_strlen(p + 1) + 1);
		}
	}
	idx = 0;
	if (ft_strchr(cmd[0], '//'))
	{

	}
	else if
	{
		
	}
}