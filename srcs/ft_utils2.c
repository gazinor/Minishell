/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:26:19 by glaurent          #+#    #+#             */
/*   Updated: 2020/06/29 20:48:13 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_ereaser(char *str, char c)
{
	int 	i;
	int		j;
	char	*cpy;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			j++;
		i++;
	}
	if (!(cpy = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			cpy[j] = str[i];
			j++;
		}
		i++;
	}
	cpy[j] = '\0';
	free_string(&str);
	return (cpy);
}

int		relink(t_data *data)
{
	char	*str;
	char	*cpy;
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
	while(data->ultimate_tab[i])
	{
		if (i == 0)
		{
			str = ft_strjoin(str, data->ultimate_tab[i]);
			free_string(&data->ultimate_tab[i]);
		}
		else
		{
			cpy = ft_strjoin(str, " ");
			free_string(&str);
			str = join_n_free(cpy, data->ultimate_tab[i], 1);
		}
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
		return (-1);
	if (is_builtin(data->ultimate_check, data) == 1)
		return (0);
	else if ((data->binary = is_exec(data->ultimate_check, data)) != NULL)
	{
		check_ls(data->ultimate_check, data);
		try_exec(data, data->ultimate_check);
		return (0);
	}
	free_string(&data->exec);
	return (-1);
}