/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2_bismillah.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:23:14 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/04 02:38:20 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norme_ft_export(t_env **env, char *key, char *value)
{
	while (*env)
	{
		if (key && value && ft_strcmp((*env)->key, key) == 0)
		{
			free((*env)->value);
			(*env)->value = value;
			return ;
		}
		env = &(*env)->next;
	}
}

void	norme_ft_unset(t_data *data, t_env *copy, t_env *prev, char *key)
{
	while (copy)
	{
		if (check_char(data->option[1], '=') != -1)
		{
			ft_printf(2, "Minishell: unset: '%s': not a valid identifier\n",
					data->option[1]);
			return ;
		}
		if (ft_strcmp(copy->key, key) == 0 && key)
		{
			free(copy->value);
			free(copy->key);
			if (prev)
				prev->next = prev->next->next;
			free(copy);
			break ;
		}
		prev = copy;
		copy = copy->next;
	}
}
