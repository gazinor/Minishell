/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:10:59 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/06 20:22:41 by gaefourn         ###   ########.fr       */
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

	if ((not_split = find_key_value(data->env, "PATH")) == NULL)
		return (-1);
	data->paths = ft_split(not_split, ':');
	free_string(&not_split);
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
	data->option = NULL;
	data->token = 0;
	g_data.token2 = 0;
	data->line = NULL;
	data->ret = 0;
	data->head_file = NULL;
	data->uvar = NULL;
	data->ultimate_check = NULL;
	data->ultimate_tab = NULL;
	data->checkcd = 0;
	data->check_ret = 0;
}

void	set_up_all(t_data *data, t_cmd **head, char **envp)
{
	init_env(&data->env, envp);
	init_data(data);
	where_am_i(data);
	ft_printf(1, "\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	*head = data->cmd_lst;
}
