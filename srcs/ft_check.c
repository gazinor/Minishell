/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 01:46:54 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/10 19:34:22 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_backslash(t_data *data, int ret)
{
	char	*cpy;
	char	*tmp;

	cpy = ft_substr(data->line, 0, ret - 1);
	tmp = ft_strjoin(cpy, &data->line[ret]);
	free(cpy);
	cpy = tmp;
	free_string(&data->line);
	data->line = ft_strdup(cpy);
	free(cpy);
	return (1);
}

int		check_line(t_data *data)
{
	int		ret;

	ret = -1;
	while (data->line[++ret])
		if (data->line[ret] == '\\')
			ft_backslash(data, ret + 1);
	ret = -1;
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

void	norme_ft_dollar(t_data *data, char *cpy, char *cpy2, int i)
{
	char *tmp;
	char *tmp2;

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
		return (0);
	if (data->line[i] == '$')
		i++;
	while (data->line[i] && data->line[i] != ' ' && data->line[i] != '/'
			&& data->line[i] != '$' && data->line[i] != '"' &&
			data->line[i] != '\'')
		i++;
	norme_ft_dollar(data, cpy, cpy2, i);
	return (1);
}
