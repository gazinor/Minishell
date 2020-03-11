/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:42:18 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/11 23:14:43 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	check_ls(char *str, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	skip_white(str, &i);
	if (str[i] == 'l' && str[i + 1] == 's' &&
			(str[i + 2] == ' ' || str[i + 2] == '\0'))
	{
		tmp = join_n_free(join_n_free(ft_substr(str, i, i + 2),
					ft_strdup(" -G"), 0), ft_strdup(str + i + 2), 0);
		data->option = ft_split(tmp, ' ');
		free(tmp);
		return ;
	}
	else
		data->option = ft_split(str, ' ');
	return ;
}

void	handle_sigint(int signum)
{
	(void)signum;
	ft_printf(1, "\e[D\e[D  ");
	ft_printf(1, "\n\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", g_data.here);
	g_data.token = 1;
}

void	handle_sigquit(int signum)
{
	ft_printf(1, "\e[D\e[D  \e[D\e[D");
	(void)signum;
	g_data.token2 = 1;
}

int		main(int ac, char **av, char **envp)
{
	t_data	*data;
	t_cmd	*head;

	data = &g_data;
	(void)ac;
	(void)av;
	set_up_all(data, &head, envp);
	main_loop(data, head);
	return (42);
}
