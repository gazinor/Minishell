/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 19:02:32 by glaurent          #+#    #+#             */
/*   Updated: 2020/07/06 21:25:45 by gaefourn         ###   ########.fr       */
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
