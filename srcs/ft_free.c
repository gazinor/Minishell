/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:44:08 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/10 05:59:58 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_file *file)
{
	t_file *prev;

	while (file)
	{
		prev = file;
		file = file->next;
		free(prev);
		prev = NULL;
	}
	free(file);
	file = NULL;
}

void	free_tab(char ***tab)
{
	int i;

	if (*tab)
	{
		i = -1;
		while ((*tab)[++i])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
		free(*tab);
		*tab = NULL;
	}
}

void	free_string(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_lst_cmd(t_cmd **cmd)
{
	t_cmd	*prev;

	while (*cmd)
	{
		prev = *cmd;
		free_lst((*cmd)->file);
		free_string(&(*cmd)->cmd);
		*cmd = (*cmd)->next;
		free(prev);
		prev = NULL;
	}
	free(*cmd);
	*cmd = NULL;
}
