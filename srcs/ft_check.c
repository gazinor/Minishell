/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 01:46:54 by gaefourn          #+#    #+#             */
/*   Updated: 2020/02/21 02:14:50 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_line(t_data *data)
{
	int ret;

	if ((ret = check_char(data->line, '$')) != -1)
		return(ft_dollar(data, ret));
//	else if (check_char(data->line, ';') != -1)
//		ft_ptvirgule(data);
//	else if (check_char(data->line, '|') != -1)
//		ft_pipe(data);
	return (0);
}

int	ft_dollar(t_data *data, int ret)
{
	char	*cpy;
	char	*cpy2;
	int		i;

	cpy = NULL;
	cpy2 = NULL;
	i = ret;
	cpy = ft_substr(data->line, 0, ret);
	dollar_case(data->line, &ret, data, 2);
	if (data->line[i] == '$' && (data->line[i + 1] == ' ' ||
			data->line[i + 1] == '"' || data->line[i + 1] == '\0'))
		return (0);
	if (data->line[i] == '$')
		i++;
	while (data->line[i] && data->line[i] != ' ' && data->line[i] != '/' && data->line[i] != '$' && data->line[i] != '"')
		i++;
	cpy2 = ft_strdup(data->line + i);
	cpy = ft_strjoin(cpy, data->value);
	cpy = ft_strjoin(cpy, cpy2);
	data->line = ft_strdup(cpy);
	free(cpy);
	return (1);
}
