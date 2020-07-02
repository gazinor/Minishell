/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:26:19 by glaurent          #+#    #+#             */
/*   Updated: 2020/07/02 19:19:31 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_string_around(char *str, char *c, int pos, int keep)
{
	char	*cpy;
	char	*cpy2;

	cpy2 = ft_substr(str, pos, 1);
	cpy = ft_substr(str, 0, pos - (keep == 0 ? 1 : 0));
	cpy = join_n_free(cpy, c, 42);
	cpy = join_n_free(cpy, cpy2, 1);
	cpy = join_n_free(cpy, c, 42);
	cpy = join_n_free(cpy, &str[pos + 1], 42);
	free_string(&str);
	return (cpy);
}

char	*quote_ereaser(char *str)
{
	int		i;
	int		j;
	char	*cpy;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i++] == '\'')
		{
			skip_char(str, &i, str[i - 1]);
			j -= 2;
		}
		if (str[i])
			i++;
	}
	if (!(cpy = malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
		norme_quote_ereaser(str, &cpy, &i, &j);
	cpy[j] = '\0';
	free_string(&str);
	return (cpy);
}

int		relink(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (data->ultimate_tab[0][i])
	{
		if (data->ultimate_tab[0][i] == ' ')
			return (-1);
		i++;
	}
	i = 0;
	while (data->ultimate_tab[i])
	{
		norme_relink(&str, i, data);
		i++;
	}
	data->ultimate_check = ft_strdup(str);
	free(data->ultimate_tab);
	free_string(&str);
	return (0);
}

int		ultimate_check(t_data *data)
{
	free_string(&data->exec);
	if (relink(data) == -1)
	{
		free_tab(&data->ultimate_tab);
		free(data->ultimate_tab);
		return (-1);
	}
	if (is_builtin(data->ultimate_check, data) == 1)
		return (0);
	else if ((data->binary = is_exec(data->ultimate_check, data)) != NULL)
	{
		check_ls(data->ultimate_check, data);
		try_exec(data, data->ultimate_check);
		return (0);
	}
	free_string(&data->exec);
	return (-42);
}
