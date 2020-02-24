/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 01:46:54 by gaefourn          #+#    #+#             */
/*   Updated: 2020/02/24 18:50:27 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_backslash(t_data *data, int ret)
{
	char	*cpy;
	char	*tmp;

	cpy = NULL;
	cpy = ft_substr(data->line, 0, ret - 1);
	tmp = ft_strjoin(cpy, &data->line[ret]);
	free(cpy);
	cpy = tmp;
	data->line = ft_strdup(cpy);
	free(cpy);
	return (1);
}

int		check_line(t_data *data)
{
	int ret;

	ret = -1;
	if (check_char(data->line, '\\') != -1)
		while (data->line[++ret])
		{
			if (data->line[ret] == '\\')
				ft_backslash(data, ret + 1);
		}
	if (check_char(data->line, '$') != -1)
		while (data->line[++ret])
		{
			if (data->line[ret] == '\'')
				while (data->line[++ret] && data->line[ret] != '\'')
					;
			if (data->line[ret] == '"')
				while (data->line[++ret] && data->line[ret] != '"')
					if (data->line[ret] == '$')
						ft_dollar(data, ret);
			if (data->line[ret] == '$')
				ft_dollar(data, ret);
		}
//	else if (check_char(data->line, ';') != -1)
//		ft_ptvirgule(data);
//	else if (check_char(data->line, '|') != -1)
//		ft_pipe(data);
	return (0);
}

int		ft_dollar(t_data *data, int ret)
{
	char	*cpy;
	char	*cpy2;
	char	*tmp;
	char	*tmp2;
	int		i;

	cpy = NULL;
	cpy2 = NULL;
	i = ret;
	cpy = ft_substr(data->line, 0, ret);
	dollar_case(data->line, &ret, data, 2);
	if (data->line[i] == '$' && (data->line[i + 1] == ' ' ||
			data->line[i + 1] == '"' || data->line[i + 1] == '\0' ||
			data->line[i + 1] == '?'))
		return (0);
	if (data->line[i] == '$')
		i++;
	while (data->line[i] && data->line[i] != ' ' && data->line[i] != '/'
			&& data->line[i] != '$' && data->line[i] != '"' && data->line[i] != '\'')
		i++;
	cpy2 = ft_strdup(data->line + i);
	tmp = ft_strjoin(cpy, data->value);
	free(cpy);
	cpy = tmp;
	tmp2 = ft_strjoin(cpy, cpy2);
	free(cpy);
	free(cpy2);
	cpy = tmp2;
	data->line = ft_strdup(cpy);
	free(cpy);
	return (1);
}
