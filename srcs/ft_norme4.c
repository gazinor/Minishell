/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 19:02:32 by glaurent          #+#    #+#             */
/*   Updated: 2020/07/02 19:05:56 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_error(t_data *data)
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
