/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 04:35:06 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/01 19:01:39 by gaefourn         ###   ########.fr       */
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

	cpy = NULL;
	head = data->env;
	while (data->env)
	{
		add_new_elem(&cpy, ft_strdup(data->env->key),
				ft_strdup(data->env->value));
		data->env = data->env->next;
	}
	data->env = head;
	ft_sort_list(&cpy);
	while (cpy)
	{
		ft_printf(1, "declare -x %s=%s\n", cpy->key, cpy->value);
		cpy = cpy->next;
	}
}

void	ft_export(char *str, t_env **env, t_data *data)
{
	char	*key;
	char	*value;
	int		egal;

	data->option = ft_split(str, ' ');
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
	add_new_elem(env, key, value);
}

void	ft_unset(char *str, t_data *data)
{
	t_env	*prev;
	t_env	*copy;
	char	*key;

	data->option = ft_split(str, ' ');
	if (data->option[1])
		key = ft_strdup(data->option[1]);
	else
		return ;
	prev = NULL;
	copy = data->env;
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
			break;
		}
		prev = copy;
		copy = copy->next;
	}
}

void	skip_white(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		++*i;
}

char	*get_next_word(char *str, int *i)
{
	int		j;

	if (str[++*i] == ' ' || !str[*i])
		return (ft_strdup("$"));
	--*i;
	j = 0;
	while (str[++*i] && str[*i] != ' ' && str[*i] != '\t' &&
			str[*i] != '"' && str[*i] != '\'' && str[*i] != '/' && str[*i] != '$')
		++j;
	return (ft_substr(str, *i - j, j));
}

void	dollar_case(char *str, int *i, t_data *data, int check)
{
	char	*word;

	word = get_next_word(str, i);
	if (check == 1 && ft_strcmp(word, "$") == 0)
		ft_printf(1, "%s", word);
	if (!(data->value = find_key_value(data->env, word)))
	{
		//skip_white(str, i);
		//--*i;
		return ;
	}
	else
		check == 1 ? ft_printf(1, "%s ", data->value) : 1;
	skip_white(str, i);
	--*i;
	free(word);
}

char	*join_n_free(char *s1, char *s2)
{
	char	*cpy;

	cpy = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (cpy);
}

int     simple_quote(char *str, int *i)
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

int     double_quote(char *str, int *i, t_data *data)
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
			str[*i + 1] == '?' ? ft_printf(1, "%d", data->ret) : ft_printf(1, "$");
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
	(void)data;

	i = 0;
	j = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i])
		i++;
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	if (str[i] == '-' && str[i + 1] == 'n' && (str[i+ 2] == ' ' || str[i + 2] == '\0'))
	{
		j = 1;
		i += 3;
	}
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (double_quote(str, &i, data) == -1)
				return ;
		}
		else if (str[i] == '\'')
		{
			if (simple_quote(str, &i) == -1)
				return ;
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			ft_printf(1, "%d", data->ret);
			i++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
		{
			write(1, " ", 1);
			skip_white(str, &i);
			--i;
		}
		else if (str[i] == '$' && str[i + 1] == '?')
			;
		else
			ft_printf(1, "%c", str[i]);
		i++;
	}
	if (j == 0)
		write(1,"\n", 1);
}
