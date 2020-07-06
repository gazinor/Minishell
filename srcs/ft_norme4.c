/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 19:02:32 by glaurent          #+#    #+#             */
/*   Updated: 2020/07/06 22:25:02 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redir_error(t_data *data)
{
	t_cmd *tmp;

	ft_clear_file_lst(&data->head_file, data);
	free_string(&data->cmd_lst->pipe->cmd);
	free(data->cmd_lst->pipe);
	tmp = data->cmd_lst;
	data->cmd_lst = data->cmd_lst->next;
	free(tmp);
	return (-1);
}

int		check_string(char *str)
{
	int i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (-1);
	while (str[i])
	{
		if ((str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') &&
			(str[i] <= '0' || str[i] >= '9') && str[i] != '=')
			return (-1);
		if (str[i] == '=')
			return (-2);
		i++;
	}
	return (1);
}

void	lol(char **key, char **value)
{
	free_string(key);
	free_string(value);
}

int		norme_env(t_data *data)
{
	if (data->option[1] && data->option[1][0] == '=')
	{
		ft_printf(2, "env: setenv %s: Invalid argument\n", data->option[1]);
		data->check_ret = 1;
		return (-1);
	}
	if (data->option[1] && check_char(data->option[1], '=') == -1)
	{
		if (open(data->option[1], O_APPEND) != -1 &&
			data->option[1][ft_strlen(data->option[1]) - 1] == '/')
		{
			ft_printf(2, "env: %s: Permission denied\n", data->option[1]);
			data->check_ret = 126;
			return (-1);
		}
		ft_printf(2, "env: %s: No such file or directory\n", data->option[1]);
		data->check_ret = 127;
		return (-1);
	}
	return (0);
}
