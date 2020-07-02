/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 01:34:08 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/02 19:39:59 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norme_display_output(t_data *data)
{
	data->ultimate_tab = ft_splitv2(data->cmd_lst->pipe->cmd, ' ', data);
	data->option = ft_splitv2(data->cmd_lst->pipe->cmd, ' ', data);
	if ((data->ufree = ultimate_check(data)) < 0)
	{
		data->ret = 127;
		ft_printf(2, "Minishell: command not found: %s\n", data->option[0]);
	}
	free_string(&data->ultimate_check);
}

void	free_main_loop(t_data *data)
{
	free_string(&data->line);
	free_string(&data->value);
}

void	norme_splitv2(t_s *t, char c, const char *s)
{
	t->k = t->j - 1;
	skip_char((char *)s, &t->j, s[t->j - 1]);
	while (s[t->j] && s[++t->j] != c && s[t->j])
		if ((s[t->j] == '"' || s[t->j] == '\'') && s[t->j + 1])
		{
			++t->j;
			skip_char((char *)s, &t->j, s[t->j - 1]);
		}
	t->strs[t->i] = ft_substr(s, t->k, (t->j - t->k));
	t->strs[t->i] = quote_ereaser(t->strs[t->i]);
	++t->i;
	if (s[t->j])
		++t->j;
}

int		norme_splitv2v2(t_s *t, char c, const char *s)
{
	while (s[t->j] == c && s[t->j])
		++t->j;
	if ((s[t->j] == '"' || s[t->j] == '\'') && ++t->j)
	{
		norme_splitv2(t, c, s);
		return (-1);
	}
	return (0);
}

void	init_t(t_s *t)
{
	t->i = 0;
	t->j = 0;
	t->k = 0;
}
