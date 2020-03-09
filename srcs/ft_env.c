/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:10:59 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/09 01:02:22 by gaefourn         ###   ########.fr       */
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

int		get_paths(t_data *data)
{
	char	*not_split;
	int		i;

	i = -1;
	if (data->paths)
	{
		while(data->paths[++i])
			free(data->paths[i]);
		free(data->paths);
		data->paths = NULL;
	}
	if ((not_split = find_key_value(data->env, "PATH")) == NULL)
		return (-1);
	data->paths = ft_split(not_split, ':');
	free(not_split);
	return (0);
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

void	init_data(t_data *data)
{
	data->pwd = NULL;
	data->cmd_lst = NULL;
	data->binary = NULL;
	data->paths = NULL;
}
