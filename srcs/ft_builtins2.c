/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 04:35:06 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/14 08:48:01 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_elem(t_env **env, char *key, char *value)
{
	while (*env)
		env = &(*env)->next;
	if (!(*env = malloc(sizeof(t_env))))
		exit(1);
	(*env)->key = key;
	(*env)->value = value;
	(*env)->next = NULL;
}

void	ft_export(char *str, t_env **env, t_data *data)
{
	char	*key;
	char	*value;
	int		egal;

	data->option = ft_split(str, ' ');
	if (data->option && (egal = check_char(data->option[1], '=')) != 0)
	{
		key = ft_substr(data->option[1], 0, egal);
		value = ft_strdup(data->option[1] + egal + 1);
	}
	while (*env)
	{
		if (ft_strcmp((*env)->key, key) == 0 && key && value)
		{
			free((*env)->value);
			(*env)->value = value;
			return ;
		}
		env = &(*env)->next;
	}
	add_new_elem(env, key, value);
}

void	ft_unset(char *str, t_data *data)
{
	t_env	*prev;
	t_env	*copy;
	char	*key;

	data->option = ft_split(str, ' ');
	if (data->option)
		key = ft_strdup(data->option[1]);
	prev = NULL;
	copy = data->env;
	while (copy)
	{
		if (ft_strcmp(copy->key, key) == 0 && key)
		{
			free(copy->value);
			free(copy->key);
			if (prev)
				prev->next = prev->next->next;
			free(copy);
			break;
		}
		prev = copy;
		copy = copy->next;
	}
}
