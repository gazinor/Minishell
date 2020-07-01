/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:04:52 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/01 23:32:32 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_elem(t_env **env, char *key, char *value)
{
	while (*env)
		env = &(*env)->next;
	if (!(*env = malloc(sizeof(t_env))))
		exit(1);
	(*env)->key = ft_strdup(key);
	(*env)->value = ft_strdup(value);
	(*env)->next = NULL;
}

void	ft_sort_list(t_env **copy)
{
	t_env	*head;
	char	*tmp;

	head = (*copy);
	while ((*copy) && (*copy)->next)
	{
		if (ft_strcmp((*copy)->key, (*copy)->next->key) > 0)
		{
			tmp = (*copy)->key;
			(*copy)->key = (*copy)->next->key;
			(*copy)->next->key = tmp;
			tmp = (*copy)->value;
			(*copy)->value = (*copy)->next->value;
			(*copy)->next->value = tmp;
			(*copy) = head;
		}
		else
			(*copy) = (*copy)->next;
	}
	(*copy) = head;
}

void	display_sort(t_data *data)
{
	t_env	*cpy;
	t_env	*head;
	t_env	*tmp;

	cpy = NULL;
	head = data->env;
	while (data->env)
	{
		add_new_elem(&cpy, data->env->key, data->env->value);
		data->env = data->env->next;
	}
	data->env = head;
	ft_sort_list(&cpy);
	while (cpy)
	{
		ft_printf(1, "declare -x %s=%s\n", cpy->key, cpy->value);
		free_string(&cpy->key);
		free_string(&cpy->value);
		tmp = cpy;
		cpy = cpy->next;
		free(tmp);
	}
}

void	skip_white(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		++*i;
}

char	*get_next_word(char *str, int *i)
{
	int	j;

	if (str[++*i] == ' ' || !str[*i])
		return (ft_strdup("$"));
	--*i;
	j = 0;
	while (str[++*i] && str[*i] != ' ' && str[*i] != '\t' &&
			str[*i] != '"' && str[*i] != '\'' &&
			str[*i] != '/' && str[*i] != '$')
		++j;
	return (ft_substr(str, *i - j, j));
}
