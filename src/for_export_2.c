/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:13:35 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/24 15:17:56 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
