/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 03:27:28 by gaefourn          #+#    #+#             */
/*   Updated: 2020/06/24 18:19:07 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norme_ft_ptvirgule2(char **str, int *i)
{
	char *tmp;

	tmp = ft_strdup(*str + *i + 1);
	free_string(str);
	*str = ft_strdup(tmp);
	free_string(&tmp);
	*i = -1;
}

int		norme_ft_main_loop(t_data *data)
{
	if (data->line[0] == '$' && data->line[1] == '?')
	{
		ft_printf(2, "Minishell: %d command not found\n", data->ret);
		data->ret = 127;
		ft_printf(1, "\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
		free_string(&data->line);
		free_string(&data->value);
		return (-1);
	}
	return (0);
}

int		norme_ft_count_pipe(char *str, int i, char *tmp)
{
	if (str[i] == '|' && str[i + 1] == '|' && str[i + 2])
	{
		ft_printf(2,
			"Minishell: syntax error near unexpected token `||'\n");
		free_string(&tmp);
		return (-1);
	}
	return (0);
}

void	norme_ft_count_pipe2(char **str, int *i)
{
	char	*tmp;

	tmp = ft_strdup(*str + (*i + 1));
	free_string(str);
	*str = ft_strdup(tmp);
	free_string(&tmp);
	*i = -1;
}

void	norme_ft_cd(char *str)
{
	char	**tab;

	tab = ft_splitv2(str, ' ');
	ft_printf(2, "cd: %s: %s\n", strerror(errno), tab[0]);
	free_tab(&tab);
}
