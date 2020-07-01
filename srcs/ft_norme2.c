/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 17:59:12 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/01 01:23:44 by gaefourn         ###   ########.fr       */
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

void	la_norme(t_data *data, char *tmp)
{
	display_output(data, tmp);
	exit(data->ret);
}

void	norme_relink(char **str, int i, t_data *data)
{
	if (i == 0)
	{
		*str = ft_strjoin(*str, data->ultimate_tab[i]);
		free_string(&data->ultimate_tab[i]);
	}
	else
	{
		*str = join_n_free(*str, " ", 42);
		*str = join_n_free(*str, "\"", 42);
		*str = join_n_free(*str, data->ultimate_tab[i], 1);
		*str = join_n_free(*str, "\"", 42);
	}
}

void	norme_quote_ereaser(char *str, char **cpy, int *i, int *j)
{
	if (str[*i] == '"' && ++*i)
		while (str[*i] && str[*i] != '"')
		{
			(*cpy)[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
	else if (str[*i] == '\'' && ++*i)
		while (str[*i] && str[*i] != '\'')
		{
			(*cpy)[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
	else
	{
		(*cpy)[*j] = str[*i];
		(*j)++;
	}
	if (str[*i])
		(*i)++;
}

int		return_value(t_data *data)
{
	free_string(&data->uvar);
	return (-1);
}
