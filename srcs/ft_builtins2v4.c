/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2v4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:23:14 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/06 21:20:04 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		norme_ft_export(t_env **env, char *key, char *value)
{
	while (*env)
	{
		if (key && value && ft_strcmp((*env)->key, key) == 0)
		{
			free_string(&(*env)->value);
			(*env)->value = ft_strdup(value);
			return (1);
		}
		env = &(*env)->next;
	}
	return (0);
}

void	norme_ft_unset(t_data *data, t_env *copy, t_env *prev, char *key)
{
	while (copy)
	{
		if (check_char(data->option[1], '=') != -1 ||
			check_string(data->option[1]) <= -1)
		{
			ft_printf(2, "Minishell: unset: '%s': not a valid identifier\n",
					data->option[1]);
			data->check_ret = 1;
			return ;
		}
		if (ft_strcmp(copy->key, key) == 0 && key)
		{
			free_string(&copy->value);
			free_string(&copy->key);
			if (prev)
				prev->next = prev->next->next;
			free(copy);
			break ;
		}
		prev = copy;
		copy = copy->next;
	}
}

void	norme_ft_export_bis(t_data *data, char **key, char **value, int egal)
{
	*key = ft_substr(data->option[1], 0, egal);
	*value = ft_strdup(data->option[1] + egal + 1);
}
