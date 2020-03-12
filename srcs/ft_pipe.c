/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 01:30:15 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/12 03:24:07 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_pipe(t_pipe **pipe, char *str)
{
	int	i;

	i = 0;
	skip_white(str, &i);
	while ((*pipe))
		pipe = &(*pipe)->next;
	if (!((*pipe) = malloc(sizeof(t_pipe))))
		exit(-1);
	(*pipe)->cmd = str;
	(*pipe)->file = NULL;
	(*pipe)->next = NULL;
	if (str[i] == '\0')
	{
		str[0] = '\0';
		return (str);
	}
	return ((*pipe)->cmd);
}

int		count_pipe(t_pipe **pipe, char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '|' && str[i + 1] == '|' && str[i + 2])
		{
			ft_printf(2, "Minishell: syntax error near unexpected token `||'\n");
			free_string(&tmp);
			return (-1);
		}
		else if (str[i] == '|')
		{
			if (!*add_pipe(pipe, ft_substr(str, 0, i)))
				{
					ft_printf(2,
						"Minishell: syntax error near unexpected token `|'\n");
					free_string(&tmp);
					return (-1);
				}
			tmp = ft_strdup(str + i + 1);
			free_string(&str);
			str = ft_strdup(tmp);
			free_string(&tmp);
			i = -1;
		}
	}
	add_pipe(pipe, ft_substr(str, 0, i));
	return (0);
}
