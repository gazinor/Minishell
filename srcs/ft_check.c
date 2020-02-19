/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 01:46:54 by gaefourn          #+#    #+#             */
/*   Updated: 2020/02/19 02:55:02 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_line(t_data *data)
{
	int ret;

	if ((ret = check_char(data->line, '$')) != -1)
		ft_dollar(data, ret);
//	else if (check_char(data->line, ';') != -1)
//		ft_ptvirgule(data);
//	else if (check_char(data->line, '|') != -1)
//		ft_pipe(data);
}

void	ft_dollar(t_data *data, int ret)
{
	char	*cpy;
	char	*cpy2;
	int		i;
	int		len;

	cpy = NULL;
	cpy2 = NULL;
	i = ret;
	len = ft_strlen(data->line);
	cpy = ft_substr(data->line, 0, ret);
	dollar_case(data->line, &ret, data, 2);
	while (data->line[i] && data->line[i] != ' ' && data->line[i] != '/')
		i++;
	cpy2 = ft_substr(data->line, i, len);
	cpy = ft_strjoin(cpy, data->value);
	cpy = ft_strjoin(cpy, cpy2);
	data->line = ft_strdup(cpy);
	free(cpy);
}
