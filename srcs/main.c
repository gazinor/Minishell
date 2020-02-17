/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:42:18 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/17 07:21:29 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data g_data;

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
	char **envp;

	(void)str;
	envp = ft_split_env(data->env);
	data->pid = fork();
	if (data->pid == 0)
	{
		errno = 0;
		if ((ret = execve(data->binary, data->option, envp)) != 0)
			ft_printf("Minishell: %s: %s\n",
					strerror(errno), data->exec);
		exit(ret);
	}
	if (data->pid > 0)
		wait(0);
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

int		check_ls(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'l' && str[i + 1] == 's')
			return (1);
		i++;
	}
	return (0);
}

void    handle_sigint(int signum)
{
	(void)signum;
	ft_printf("\e[D\e[D  ");
	ft_printf("\n\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", where_am_i());
	g_data.flag = 1;
}

int		loop(t_data *data)
{
	char	*tmp;
	char	*old;
	int		ret;

	tmp = NULL;
	old = NULL;
	while ((ret = get_next_line(0, &data->line)) == 0)
	{
		old = tmp ? ft_strjoin(tmp, data->line) : ft_strdup(data->line);
		free(tmp);
		free(data->line);
		data->line = NULL;
		if (old[0] == 0)
		{
			free(old);
			ft_printf("  \e[D\e[D");
			return (-1);
		}
		if (data->flag == 1)
		{
			if (data->line)
			{
				free(data->line);
				data->line = NULL;
			}
		}
		tmp = old;
	}
	if (data->flag == 1)
	{
		if (old)
			free(old);
		if (data->line)
		{
			free(data->line);
			data->line = NULL;
		}
		return (0);
	}
	if (ret > 0)
	{
		old = tmp ? ft_strjoin(tmp, data->line) : ft_strdup(data->line);
		free(tmp);
		free(data->line);
		data->line = old;
	}
	return (ret);
}

int		main(int ac, char **av, char **envp)
{
	t_data	*data;
	int		ret;

	(void)ac;
	(void)av;
	data = &g_data;
	data->line = NULL;
	data->flag = 0;
	init_env(&data->env, envp);
	data->here = where_am_i();
	data->paths = get_paths(data);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		ft_printf("\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data->here);
		if ((ret = loop(data)) == -1)
			break ;
		if (ret == 0)
			data->flag = 0;
		else if (is_builtin(data->line, data) == 1)
			;
		else if ((data->binary = is_exec(data->line, data)) != NULL)
		{
			if (check_ls(data->line) == 1)
				data->option = ft_split(ft_strjoin(data->line, " -G"), ' ');
			else
				data->option = ft_split(data->line, ' ');
			try_exec(data, data->line);
		}
		else if (data->line[0])
		{
			data->option = ft_split(data->line, ' ');
			ft_printf("Minishell: command not found: %s\n", data->option[0]);
		}
	}
	ft_exit(data);

	return (0);
}
