/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:42:18 by glaurent          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/06/25 13:40:23 by glaurent         ###   ########.fr       */
=======
/*   Updated: 2020/06/18 16:40:46 by glaurent         ###   ########.fr       */
>>>>>>> origin
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	ft_strdupv2(char *str, t_data *data)
{
	char	*cpy;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'') && ++j)
			continue ;
	}
	if (!(cpy = malloc(sizeof(char) * ((i - j) + 1))))
		return ;
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			continue ;
		cpy[j] = str[i];
		j++;
	}
	cpy[i] = '\0';
	data->tmp = cpy;
}

void	check_ls(char *str, t_data *data)
{
	int		i;
	char	*tmp;
	char	*cpy;

	i = 0;
<<<<<<< HEAD
	cpy = ft_strdup(str);
	skip_white(str, &i);
=======
	ft_strdupv2(str, data);
	cpy = ft_strdup(data->tmp);
	skip_white(cpy, &i);
>>>>>>> origin
	if (cpy[i] == 'l' && cpy[i + 1] == 's' &&
			(cpy[i + 2] == ' ' || cpy[i + 2] == '\0'))
	{
		tmp = join_n_free(join_n_free(ft_substr(cpy, i, i + 2),
					ft_strdup(" -G"), 0), ft_strdup(cpy + i + 2), 0);
<<<<<<< HEAD
		data->option = ft_splitv2(tmp, ' ', data);
		free_string(&data->tmp);
		free_string(&cpy);
		free_string(&tmp);
		return ;
	}
	else
		data->option = ft_splitv2(cpy, ' ', data);
=======
		data->option = ft_split(tmp, ' ');
		free_string(&data->tmp);
		free_string(&cpy);
		free(tmp);
		return ;
	}
	else
		data->option = ft_split(cpy, ' ');
>>>>>>> origin
	free_string(&data->tmp);
	free_string(&cpy);
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
	t_cmd	*prev;

	data = &g_data;
	(void)ac;
	(void)av;
	prev = NULL;
	set_up_all(data, &head, envp);
	main_loop(data, head);
	return (42);
}
