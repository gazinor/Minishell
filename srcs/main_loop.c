/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:16:51 by gaefourn          #+#    #+#             */
/*   Updated: 2020/06/18 19:30:43 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_next(t_data *data)
{
	t_cmd	*prev;

	ft_clear_file_lst(&data->head_file, data);
	free_pipe(&data->cmd_lst->pipe);
	prev = data->cmd_lst;
	data->cmd_lst = data->cmd_lst->next;
	free(prev);
	prev = NULL;
	free_string(&data->exec);
	free_tab(&data->paths);
	free_tab(&data->option);
}

void	update_line(char **line, char *tmp)
{
	int i;

	i = 0;
	skip_white(*line, &i);
	free_string(&tmp);
	tmp = ft_strdup(*line + i);
	free_string(line);
	*line = tmp;
}

int		display_output(t_data *data, char *tmp)
{
	get_paths(data);
	update_line(&data->cmd_lst->pipe->cmd, tmp);
	if (data->pwd == NULL)
		ft_pwd(data->cmd_lst->pipe->cmd, data);
	if (ft_redir(data, data->cmd_lst->pipe->cmd) == -1)
	{
		ft_clear_file_lst(&data->head_file, data);
		return (-1);
	}
	if (is_builtin(data->cmd_lst->pipe->cmd, data) == 1)
		;
	else if ((data->binary = is_exec(data->cmd_lst->pipe->cmd, data)) != NULL)
	{
		check_ls(data->cmd_lst->pipe->cmd, data);
		try_exec(data, data->cmd_lst->pipe->cmd);
	}
	else if (data->cmd_lst->pipe->cmd[0])
	{
		data->option = ft_split(data->cmd_lst->pipe->cmd, ' ');
		data->ret = 127;
		ft_printf(2, "Minishell: command not found: %s\n", data->option[0]);
	}
	return (0);
}

void	loop_cmd(t_data *data, t_cmd *head, char *tmp)
{
	while (check_line(data) != 0)
		;
	if (ft_ptvirgule(data) == -1)
	{
		ft_printf(1, "\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
		free_lst_cmd(&data->cmd_lst);
		return ;
	}
	while (data->cmd_lst)
	{
		if (data->cmd_lst->pipe->next)
			ft_pipe(data->cmd_lst->pipe, data, tmp, 0);
		else if (display_output(data, tmp) == -1)
			break ;
		free_and_next(data);
	}
	data->cmd_lst = head;
	ft_printf(1, "\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
}

void	main_loop(t_data *data, t_cmd *head)
{
	int		ret;
	char	*tmp;

	tmp = NULL;
	while ((ret = get_next_line(0, &data->line)) > 0)
	{
		if (g_data.token == 1)
		{
			g_data.token = 0;
			ret == 2 && data->line[0] == '\0' ? ft_exit(data, NULL) : 1;
		}
		update_line(&data->line, tmp);
		if (norme_ft_main_loop(data) == -1)
			continue ;
		if (ret != 2)
			loop_cmd(data, head, tmp);
		else
			ft_printf(1, "  \e[D\e[D");
		free_string(&data->line);
		free_string(&data->value);
	}
	if (ret == 0)
		ft_exit(data, NULL);
}
