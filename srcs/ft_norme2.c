/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 17:59:12 by gaefourn          #+#    #+#             */
/*   Updated: 2020/06/29 21:38:23 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_ultimate_norme(char *tmp, t_data *data)
{
	char *cpy;
	char *str;
	
	cpy = NULL;

	cpy = ft_strjoin(data->pwd, "/");
	tmp = ft_strjoin(cpy, data->here);
	str = ft_strdup(tmp);
	free_string(&cpy);
	free_string(&tmp);
	return (str);
}