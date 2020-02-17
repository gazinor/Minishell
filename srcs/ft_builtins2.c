/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 04:35:06 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/17 01:10:53 by glaurent         ###   ########.fr       */
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
	else
	{
		ft_printf("Minishell: Bad assignement.\n");
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
		if (check_char(data->option[1], '=') != 0)
		{
			ft_printf("Minishell: unset: '%s': not a valid identifier\n",
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
			str[*i] != '"' && str[*i] != '\'')
		++j;
	return (ft_substr(str, *i - j, j));
}

void	dollar_case(char *str, int *i, t_data *data)
{
	char	*value;
	char	*word;

	word = get_next_word(str, i);
	if (ft_strcmp(word, "$") == 0)
		ft_printf("%s ", word);
	if (!(value = find_key_value(data->env, word)))
	{
		skip_white(str, i);
		--*i;
		return ;
	}
	else
		ft_printf("%s ", value);
	skip_white(str, i);
	--*i;
	free(word);
	free(value);
}

int		simple_quote(char *str, int *i)
{
	while (str[++*i] != '\'')
	{
		if (str[*i] == '\0')
		{
			ft_printf("Minishell: simple quote is missing\n");
			return (-1);
		}
		else
			write(1, &str[*i], 1);
	}
	return (0);
}

int		double_quote(char *str, int *i, t_data *data)
{
	while (str[++*i] != '"')
	{
		if (str[*i] == '\0')
		{
			ft_printf("Minishell: double quote is missing\n");
			return (-1);
		}
		else if (str[*i] == '$')
			dollar_case(str, i, data);
		else
			write(1, &str[*i], 1);
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
		else if (str[i] == '$')
			dollar_case(str, &i, data);
		else if (str[i] == ' ' || str[i] == '\t')
		{
			write(1, " ", 1);
			skip_white(str, &i);
			--i;
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	if (j == 0)
		write(1,"\n", 1);
}
