/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 19:10:18 by gaefourn          #+#    #+#             */
/*   Updated: 2020/06/30 00:48:07 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_norme_pipe(char **str, int *i, char **tmp, t_pipe **pipe)
{
	if (!*add_pipe(pipe, ft_substr(*str, 0, *i)))
	{
		ft_printf(2,
			"Minishell: syntax error near unexpected token `|'\n");
		free_string(tmp);
		return (-1);
	}
	norme_ft_count_pipe2(str, i);
	return (0);
}

void	ft_norme_main_pipe(t_pipe *pipes, t_data *data, int check, char *tmp)
{
	if (pipes->next)
	{
		data->cmd_lst->pipe = data->cmd_lst->pipe->next;
		ft_pipe(pipes->next, data, tmp, check + 1);
	}
	else
	{
		display_output(data, tmp);
		exit(data->ret);
	}
}
