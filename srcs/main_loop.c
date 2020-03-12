/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:16:51 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/12 02:54:57 by gaefourn         ###   ########.fr       */
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

void	ft_pipe(t_pipe *pipes, t_data *data, char *tmp, int check)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pipe(fd);
	if (!(pid1 = fork()))
	{
		close(fd[0]);
		dup2(fd[1], 1);
		exit(display_output(data, tmp));
	}
	if (!(pid2 = fork()))
	{
		close(fd[1]);
		dup2(fd[0], 0);
		if (pipes->next)
		{
			data->cmd_lst->pipe = data->cmd_lst->pipe->next;
			ft_pipe(pipes->next, data, tmp, check + 1);
		}
		else
			exit(display_output(data, tmp));
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	waitpid(pid2, &status, 0);
	if (check != 0)
		exit(status);
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
			ret == 2 && data->line[0] == '\0' ? ft_exit(data) : 1;
		}
		update_line(&data->line, tmp);
		if (data->line[0] == '$' && data->line[1] == '?')
		{
			ft_printf(2, "Minishell: %d command not found\n", data->ret);
			data->ret = 127;
			ft_printf(1, "\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
			free_string(&data->line);
			continue ;
		}
		if (ret != 2)
			loop_cmd(data, head, tmp);
		else
			ft_printf(1, "  \e[D\e[D");
		free_string(&data->line);
		ft_printf(1, "\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
	}
	if (ret == 0)
		ft_exit(data);
}
