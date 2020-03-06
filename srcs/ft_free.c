/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:44:08 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/05 22:47:56 by gaefourn         ###   ########.fr       */
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
