/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:44:08 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/01 21:46:10 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_file *file)
{
	t_file *prev;

	if (!file)
		return ;
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
			free_string(&(*tab)[i]);
			(*tab)[i] = NULL;
		}
		free(*tab);
		*tab = NULL;
	}
}

void	free_string(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_pipe(t_pipe **pipe)
{
	t_pipe	*tmp;

	if (!*pipe)
		return ;
	while (*pipe)
	{
		free_lst((*pipe)->file);
		free_string(&(*pipe)->cmd);
		tmp = *pipe;
		*pipe = (*pipe)->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_lst_cmd(t_cmd **cmd)
{
	t_cmd	*prev;

	if (!*cmd)
		return ;
	while (*cmd)
	{
		prev = *cmd;
		free_pipe(&(*cmd)->pipe);
		*cmd = (*cmd)->next;
		free(prev);
		prev = NULL;
	}
	free(*cmd);
	*cmd = NULL;
}
