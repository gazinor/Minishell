/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 01:46:54 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/02 00:44:39 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deal_with_backslashes(t_data *data, int *i)
{
	if (data->line[++*i] && data->line[*i] == '"')
	{
		data->line = put_string_around(
	put_string_around(data->line, "\"", *i, 0), "\'", *i, 1);
		*i += 3;
	}
	else
	{
		data->line = put_string_around(
	put_string_around(data->line, "\"", *i, 1), "\"", *i + 1, 1);
		*i += 4;
	}
}

void	ft_backslash(t_data *data)
{
	int		i;

	i = -1;
	while (data->line[++i])
	{
		if (data->line[i] == '\'')
			while (data->line[++i] && data->line[i] != '\'')
				;
		else if (data->line[i] == '"')
		{
			while (data->line[++i] && data->line[i] != '"')
				if (data->line[i] == '\\')
					deal_with_backslashes(data, &i);
		}
		else if (data->line[i] == '\\' && data->line[i + 1])
		{
			data->line = put_string_around(data->line,
					data->line[i + 1] == '\'' ? "\"" : "'", i + 1, 0);
			i += 2;
		}
	}
}

int		check_line(t_data *data)
{
	int		ret;

	ret = -1;
	ft_backslash(data);
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
	return (0);
}

void	norme_ft_dollar(t_data *data, char **cpy, char **cpy2, int i)
{
	char *tmp;
	char *tmp2;

	*cpy2 = ft_strdup(data->line + i);
	tmp = ft_strjoin(*cpy, data->value);
	free_string(cpy);
	*cpy = tmp;
	tmp2 = ft_strjoin(*cpy, *cpy2);
	free_string(cpy);
	free_string(cpy2);
	*cpy = tmp2;
	free_string(&data->line);
	data->line = ft_strdup(*cpy);
	free_string(cpy);
}

int		ft_dollar(t_data *data, int ret)
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
			data->line[i + 1] == '"' || data->line[i + 1] == '\0' ||
			data->line[i + 1] == '?'))
	{
		free_string(&cpy);
		return (0);
	}
	if (data->line[i] == '$')
		i++;
	while (data->line[i] && data->line[i] != ' ' && data->line[i] != '/'
			&& data->line[i] != '$' && data->line[i] != '"' &&
			data->line[i] != '\'')
		i++;
	norme_ft_dollar(data, &cpy, &cpy2, i);
	return (1);
}
