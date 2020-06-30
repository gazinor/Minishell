/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2_bis_bis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:08:47 by gaefourn          #+#    #+#             */
/*   Updated: 2020/06/30 22:32:45 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_case(char *str, int *i, t_data *data, int check)
{
	char	*word;

	word = get_next_word(str, i);
	if (check == 1 && ft_strcmp(word, "$") == 0)
		ft_printf(1, "%s", word);
	if (!(data->value = find_key_value(data->env, word)))
	{
		free_string(&word);
		return ;
	}
	else
		check == 1 ? ft_printf(1, "%s ", data->value) : 1;
	skip_white(str, i);
	--*i;
	free_string(&word);
}

char	*join_n_free(char *s1, char *s2, int size)
{
	char	*cpy;

	cpy = ft_strjoin(s1, s2);
	free_string(&s1);
	s1 = NULL;
	if (size != 42)
	{
		free_string(&s2);
		s2 = NULL;
	}
	return (cpy);
}

void	norme_ft_echo2(char *str, int *i, t_data *data)
{
	if (str[*i] == '"')
	{
		if (double_quote(str, i, data) == -1)
			return ;
	}
	else if (str[*i] == '\'')
	{
		if (simple_quote(str, i) == -1)
			return ;
	}
}

void	norme_ft_echo(char *str, int *i, t_data *data)
{
	while (str[*i])
	{
		if (str[*i] == '"' || str[*i] == '\'')
			norme_ft_echo2(str, i, data);
		else if (str[*i] == '$' && str[*i + 1] == '?')
		{
			ft_printf(1, "%d", data->ret);
			++*i;
		}
		else if (str[*i] == ' ' || str[*i] == '\t')
		{
			write(1, " ", 1);
			skip_white(str, i);
			--*i;
		}
		else if (str[*i] == '$' && str[*i + 1] == '?')
			;
		else
			ft_printf(1, "%c", str[*i]);
		++*i;
	}
}
