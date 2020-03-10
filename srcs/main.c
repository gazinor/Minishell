/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:42:18 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/10 02:46:49 by gaefourn         ###   ########.fr       */
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

void    handle_sigint(int signum)
{
	(void)signum;
	ft_printf(1, "\e[D\e[D  ");
	ft_printf(1, "\n\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", g_data.here);
	g_data.token = 1;
}

void    handle_sigquit(int signum)
{
	ft_printf(1, "\e[D\e[D  \e[D\e[D");
	(void)signum;
	g_data.token2 = 1;
}

int		main(int ac, char **av, char **envp)
{
	int		ret;
	t_data	*data;
	int		i;
	char	*tmp;
	t_cmd	*head;
	t_cmd	*prev;

	data = &g_data;
	(void)ac;
	(void)av;
	set_up_all(data, &head, envp);
	while ((ret = get_next_line(0, &data->line)) > 0)
	{
		if (g_data.token == 1)
		{
			g_data.token = 0;
			ret == 2 && data->line[0] == '\0' ? ft_exit(data) : 1;
		}
		i = 0;
		skip_white(data->line, &i);
		tmp = ft_strdup(data->line + i);
		free(data->line);
		data->line = tmp;
		if (data->line[0] == '$' && data->line[1] == '?')
		{
			ft_printf(2, "Minishell: %d command not found\n", data->ret);
			data->ret = 127;
			ft_printf(1, "\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
			continue ;
		}
		if (ret != 2)
		{
			while (check_line(data) != 0)
				;
			ft_ptvirgule(data);
			while (data->cmd_lst)
			{
				get_paths(data);
				i = 0;
				skip_white(data->cmd_lst->cmd, &i);
				tmp = ft_strdup(data->cmd_lst->cmd + i);
				free(data->cmd_lst->cmd);
				data->cmd_lst->cmd = tmp;
				if (data->pwd == NULL)
					ft_pwd(data->cmd_lst->cmd, data);
				if (ft_redir(data, data->cmd_lst->cmd) == -1)
				{
					ft_clear_file_lst(&data->head_file, data);
					break ;
				}
				if (is_builtin(data->cmd_lst->cmd, data) == 1)
					;
				else if ((data->binary = is_exec(data->cmd_lst->cmd, data)) != NULL)
				{
					check_ls(data->cmd_lst->cmd, data);
					try_exec(data, data->cmd_lst->cmd);
				}
				else if (data->cmd_lst->cmd[0])
				{
					data->option = ft_split(data->cmd_lst->cmd, ' ');
					data->ret = 127;
					ft_printf(2, "Minishell: command not found: %s\n", data->option[0]);
				}
				ft_clear_file_lst(&data->head_file, data);
				free_string(&data->cmd_lst->cmd);
				prev = data->cmd_lst;
				data->cmd_lst = data->cmd_lst->next;
				free(prev);
				free_string(&data->exec);
				free_tab(&data->paths);
				free_tab(&data->option);
			}
			ft_printf(1, "\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
			data->cmd_lst = head;
		}
		else
			ft_printf(1, "  \e[D\e[D");
		free(data->line);
	}
	if (ret == 0)
		ft_exit(data);
	return (42);
}
