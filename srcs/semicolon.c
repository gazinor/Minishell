/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 00:21:40 by glaurent          #+#    #+#             */
/*   Updated: 2020/07/06 22:36:04 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_cmd(t_cmd **cmd_lst, char **str)
{
	int i;

	i = 0;
	skip_white(*str, &i);
	if ((*str)[i] == '\0')
		return ("");
	while ((*cmd_lst))
		cmd_lst = &(*cmd_lst)->next;
	if (!((*cmd_lst) = malloc(sizeof(t_cmd))))
		exit(-1);
	(*cmd_lst)->pipe = NULL;
	(*cmd_lst)->next = NULL;
	if (count_pipe(&(*cmd_lst)->pipe, str) == -1)
		return (NULL);
	return ((*cmd_lst)->pipe->cmd);
}

int		skip_char(char *str, int *i, char c)
{
	while (str[*i] && str[*i] != c)
		++*i;
	if (!str[*i])
		return (-1);
	return (1);
}

int		norme_ft_ptvirgule(t_data *data, int *i)
{
	if (data->line[*i] == ';' && data->line[*i + 1] == ';')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `;;'\n");
		return (-1);
	}
	else if (data->line[*i] && data->line[*i] == '\'' && ++*i)
	{
		skip_char(data->line, i, '\'');
		if (data->line[*i] == '\0')
		{
			ft_printf(2, "\rMinishell: simple quote is missing\n");
			return (-1);
		}
	}
	else if (data->line[*i] && data->line[*i] == '"')
	{
		++*i;
		skip_char(data->line, i, '"');
		if (data->line[*i] == '\0')
		{
			ft_printf(2, "\rMinishell: double quote is missing\n");
			return (-1);
		}
	}
	return (0);
}

int		ft_ptvirgule(t_data *data)
{
	int		i;
	char	*save;

	i = -1;
	while (data->line[++i])
	{
		if (norme_ft_ptvirgule(data, &i) == -1)
			return (-1);
		if (data->line[i] == ';' && (data->uvar = ft_substr(data->line, 0, i)))
		{
			if (!(save = add_cmd(&data->cmd_lst, &data->uvar)))
				return (return_value(data));
			else if (!*save)
			{
				ft_printf(2,
						"Minishell: syntax error near unexpected token `;'\n");
				return (return_value(data));
			}
			norme_ft_ptvirgule2(&data->line, &i);
		}
	}
	data->uvar = ft_substr(data->line, 0, i);
	if (!(save = add_cmd(&data->cmd_lst, &data->uvar)))
		return (return_value(data));
	return (0);
}
