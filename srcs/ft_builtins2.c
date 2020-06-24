/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 04:35:06 by glaurent          #+#    #+#             */
/*   Updated: 2020/06/24 19:56:17 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char *str, t_env **env, t_data *data)
{
	char	*key;
	char	*value;
	int		egal;

	data->option = ft_splitv2(str, ' ', data);
	if (!data->option[1])
	{
		display_sort(data);
		return ;
	}
	if (data->option && (egal = check_char(data->option[1], '=')) != -1)
	{
		key = ft_substr(data->option[1], 0, egal);
		value = ft_strdup(data->option[1] + egal + 1);
	}
	else
	{
		ft_printf(2, "Minishell: Bad assignement.\n");
		return ;
	}
	norme_ft_export(env, key, value);
	add_new_elem(env, key, value);
	free(key);
	free(value);
}

void	ft_unset(char *str, t_data *data)
{
	t_env	*prev;
	t_env	*copy;
	char	*key;

	data->option = ft_splitv2(str, ' ', data);
	if (data->option[1])
		key = ft_strdup(data->option[1]);
	else
		return ;
	prev = NULL;
	copy = data->env;
	norme_ft_unset(data, copy, prev, key);
	free(key);
}

int		simple_quote(char *str, int *i)
{
	if (check_char(str + *i + 1, '\'') == -1)
	{
		ft_printf(2, "\rMinishell: simple quote is missing\n");
		return (-1);
	}
	while (str[++*i] != '\'')
		ft_printf(1, "%c", str[*i]);
	return (0);
}

int		double_quote(char *str, int *i, t_data *data)
{
	if (check_char(str + *i + 1, '"') == -1)
	{
		ft_printf(2, "\rMinishell: double quote is missing\n");
		return (-1);
	}
	while (str[++*i] != '"')
	{
		if (str[*i] == '$')
		{
			str[*i + 1] == '?' ? ft_printf(1, "%d", data->ret) :
				ft_printf(1, "$");
			if (str[*i + 1] == '?')
				++*i;
		}
		else
			ft_printf(1, "%c", str[*i]);
	}
	return (0);
}

void	ft_echo(char *str, t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i])
		i++;
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	if (str[i] == '-' && str[i + 1] == 'n' &&
			(str[i + 2] == ' ' || str[i + 2] == '\0'))
	{
		j++;
		i += 3;
	}
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	norme_ft_echo(str, &i, data);
	if (j == 0)
		write(1, "\n", 1);
}
