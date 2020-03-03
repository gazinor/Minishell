/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:42:18 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/03 03:21:55 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

char	*get_option(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && (str[i] != ' ' || str[i] != '\t'))
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i + j] && (str[i + j] != ' ' || str[i + j] != '\t'))
		j++;
	return (ft_substr(str, i, j));
}

char	*get_exec(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i + j] && (str[i + j] != ' ' && str[i + j] != '\t'))
		j++;
	return (ft_substr(str, i, j));
}

void	try_exec(t_data *data, char *str)
{
	int		ret;
	char	**envp;
	int		status;

	(void)str;
	envp = ft_split_env(data->env);
	data->pid = fork();
	data->ret = 0;
	if (data->pid == 0)
	{
		errno = 0;
		int i = -1;
		while (data->option[++i])
			ft_printf(2, "option[%d] : |%s|\n", i, data->option[i]);
		if ((ret = execve(data->binary, data->option, envp)) != 0)
			ft_printf(2, "Minishell: %s: %s\n", data->exec,
					strerror(errno));
		data->ret = ret;
		exit(ret);
	}
	if (data->pid > 0)
		wait(&status);
	data->ret = WEXITSTATUS(status);
	//fct_free_envp;
}

char	*is_exec(char *str, t_data *data)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = -1;
	data->exec = get_exec(str);
	while (data->paths[++i])
	{
		if ((dir = opendir(data->paths[i])) == NULL)
			perror("opendir() error");
		else
		{
			while ((entry = readdir(dir)) != NULL)
				if (ft_strcmp(entry->d_name, data->exec) == 0)
					return (ft_strjoin(ft_strjoin(data->paths[i], "/"),
								data->exec));
			closedir(dir);
		}
	}
	return (NULL);
}

char	**check_ls(char *str)
{
	int	i;

	i = 0;
	skip_white(str, &i);
	if (str[i] == 'l' && str[i + 1] == 's' &&
			(str[i + 2] == ' ' || str[i + 2] == '\0'))
		return (ft_split(ft_strjoin(
			ft_strjoin(ft_substr(str, 0, i + 2), " -G"), str + i + 2), ' '));
	return (ft_split(str, ' '));
}

void    handle_sigint(int signum)
{
	(void)signum;
	ft_printf(1, "\e[D\e[D  ");
	ft_printf(1, "\n\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", where_am_i());
	g_data.token = 1;
}

void    handle_sigquit(int signum)
{
	ft_printf(1, "\e[D\e[D  \e[D\e[D");
	(void)signum;
	g_data.token2 = 1;
}

void    handle_segv(int signum)
{
	ft_printf(2, "\ec");
	ft_printf(2, "\e[1mMinishell: \e[38;5;124;1mSegmentation fault\e[0;1m: error: \
\e[38;5;224;1mYOU\e[0m.\n");
	ft_printf(2, "\n%\r\e[38;5;92;1mUn segfault serieux ?                        \
        ", sleep(1));
	ft_printf(2, "%\rMais t'es une merde en fait ?                        ",
			sleep(1));
	ft_printf(2, "%\rEh mais tu segfault comme une grosse pute            ",
			sleep(1));
	ft_printf(2, "%\rEh mais ouais en fait t'es une grosse pute c'est ca ?",
			usleep(1500000));
	ft_printf(2, "%\rEh regardez c'est une grosse pute                    ",
			usleep(1500000));
	ft_printf(2, "%\rAhhhh la grosse puuuuute                             ",
			sleep(1));
	ft_printf(2, "%\r\e[38;5;202;1mCorrige ton code maintenant t'as pas de temps a\
 perdre.\n\n", sleep(1));
	exit(1);
	(void)signum;
}

void    handle_sigabrt(int signum)
{
	ft_printf(2, "\ec");
	ft_printf(2, "\e[1mMinishell: \e[38;5;124;1mSigabort\e[0;1m: error: \
\e[38;5;224;1mDevine connard\e[0m.\n");
	ft_printf(2, "\n%\r\e[38;5;92;1mUn sigabort maintenant ?", sleep(2));
	ft_printf(2, "%\rEh tu sais quoi, me parle plus.        \n\n", sleep(2));
	exit(1);
	(void)signum;
}

int		main(int ac, char **av, char **envp)
{
	int		ret;
	t_data	*data;
	int		i;
	char	*tmp;
	t_cmd	*head;

	data = &g_data;
	data->token = 0;
	g_data.token2 = 0;
	data->line = NULL;
	data->ret = 0;
	(void)ac;
	(void)av;
	init_env(&data->env, envp);
	init_data(data);
	data->here = where_am_i();
	data->head_file = NULL;
	data->paths = get_paths(data);
	ft_printf(1, "\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
//	signal(SIGSEGV, handle_segv);
//	signal(SIGABRT, handle_sigabrt);
	head = data->cmd_lst;
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
					data->option = check_ls(data->cmd_lst->cmd);
					try_exec(data, data->cmd_lst->cmd);
				}
				else if (data->cmd_lst->cmd[0])
				{
					data->option = ft_split(data->cmd_lst->cmd, ' ');
					data->ret = 127;
					ft_printf(2, "Minishell: command not found: %s\n", data->option[0]);
				}
				ft_clear_file_lst(&data->head_file, data);
				data->cmd_lst = data->cmd_lst->next;
//##################################################
//				if (data->cmd_lst.file != NULL)
//					fonction(file);
//###################################################
			}
			ft_printf(1, "\r\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
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
