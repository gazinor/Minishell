/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_norme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:58:08 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/10 20:08:11 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

void	norme_gnl(char **buff_read, char **buff, char **tmp)
{
	if (g_data.token == 1 && !*buff_read[0])
	{
		if (*buff)
			free(*buff);
		*buff = ft_strdup("");
	}
	if (*buff == NULL)
		*buff = ft_strdup(*buff_read);
	else
	{
		*tmp = ft_strjoin(*buff, *buff_read);
		free(*buff);
		*buff = *tmp;
	}
}
