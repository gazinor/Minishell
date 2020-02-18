/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:42:18 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/18 19:18:33 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

int		main(int ac, char **av, char **envp)
{
	int		ret;
	char	*line;
	t_data	data;

	line = NULL;
	(void)ac;
	(void)av;
	init_env(&data.env, envp);
	init_data(&data);
	data.here = where_am_i();
	data.paths = get_paths(&data);
	ft_printf("\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data.here);
	signal(SIGINT, handle_sigint);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (data.pwd == NULL)
			ft_pwd(line, &data);
		if (is_builtin(line, &data) == 1)
			;
		else if ((data.binary = is_exec(line, &data)) != NULL)
		{
			if (check_ls(line) == 1)
				data.option = ft_split(ft_strjoin(line, " -G"), ' ');
			else
				data.option = ft_split(line, ' ');
			try_exec(&data, line);
		}
		else if (line[0])
		{
			data.option = ft_split(line, ' ');
			ft_printf("Minishell: command not found: %s\n", data.option[0]);
		}
		ft_printf("\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data.here);
		free(line);
	}
	if (ret == 0)
		ft_exit(&data);
	return (0);
}
