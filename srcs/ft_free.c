/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:44:08 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/10 00:13:54 by gaefourn         ###   ########.fr       */
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
	
	i = -1;
	
	if (*tab)
	{
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