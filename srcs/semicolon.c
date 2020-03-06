/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 00:21:40 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 01:47:18 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_cmd(t_cmd **cmd_lst, char *str)
{
	while ((*cmd_lst))
		cmd_lst = &(*cmd_lst)->next;
	if (!((*cmd_lst) = malloc(sizeof(t_cmd))))
		exit(-1);
	(*cmd_lst)->cmd = str;
	(*cmd_lst)->file = NULL;
	(*cmd_lst)->next = NULL;
	return ((*cmd_lst)->cmd);
}

int		skip_char(char *str, int *i, char c)
{
	while (str[*i] && str[*i] != c)
		++*i;
	if (!str[*i])
		return (-1);
	return (1);
}

int	norme_ft_ptvirgule(t_data *data, int *i)
{
	if (data->line[*i] == ';' && data->line[*i + 1] == ';')
	{
		ft_printf(2, "Minishell: syntax error near unexpected token `;;'\n");
		return (-1);
	}
	else if (data->line[*i] && data->line[*i] == '\'')
	{
		++*i;
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
			return(-1);
		}
	}
	return (0);
}

void	ft_ptvirgule(t_data *data)
{
	int		i;
	char	*tmp;

	i = -1;
	while (data->line[++i])
	{
		if (norme_ft_ptvirgule(data, &i) == -1)
			return ;
		if (data->line[i] == ';')
		{
			if (!*add_cmd(&data->cmd_lst, ft_substr(data->line, 0, i)))
			{
				ft_printf(2,
						"Minishell: syntax error near unexpected token `;'\n");
				return ;
			}
			tmp = ft_strdup(data->line + i + 1);
			free(data->line);
			data->line = tmp;
			i = -1;
		}
	}
	add_cmd(&data->cmd_lst, ft_substr(data->line, 0, i));
}
