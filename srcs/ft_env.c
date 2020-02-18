/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:10:59 by gaefourn          #+#    #+#             */
/*   Updated: 2020/02/17 02:37:26 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env **env, char **envp)
{
	int i;
	int j;

	i = 0;
	while (envp[i])
	{
		if (!(*env = malloc(sizeof(t_env))))
			return ;
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				(*env)->key = ft_substr(envp[i], 0, j);
				(*env)->value = ft_strdup(envp[i] + j + 1);
				(*env)->next = NULL;
				env = &(*env)->next;
				break ;
			}
			j++;
		}
		i++;
	}
}

char	**get_paths(t_data *data)
{
	char	*not_split;

	if ((not_split = find_key_value(data->env, "PATH")) == NULL)
		ft_printf("Sorry j'ai pas trouver le path.\n");
	return (ft_split(not_split, ':'));
}

char	*find_key_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}