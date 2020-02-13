/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:42:18 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/13 22:43:22 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/ft_printf.h"
#include "gnl/get_next_line.h"
#include "../includes/minishell.h"

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

void	try_exec(t_data *data, char **envp)
{
	int		ret;

	data->pid = fork();
	if (data->pid == 0)
	{
		errno = 0;
		if ((ret = execve(data->binary, data->option, envp)) != 0)
			ft_printf("Mon premier shell: %s: %s\n",
					strerror(errno), data->exec);
		exit(ret);
	}
	if (data->pid > 0)
		wait(0);
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

int		main(int ac, char **av, char **envp)
{
	int		ret;
	char	*line;
	t_data	data;

	init_env(&data.env, envp);
	data.here = where_am_i();
	data.paths = get_paths(&data);
	ft_printf("\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data.here);
	while ((ret = get_next_line(1, &line)) > 0)
	{
		if (is_builtin(line, &data) == 1)
			;
		else if ((data.binary = is_exec(line, &data)) != NULL)
		{
			data.option = ft_split(line, ' ');
			try_exec(&data, envp);
		}
		ft_printf("\e[38;5;128m➔\e[38;5;208;1m  %s\e[0m ", data.here);
		free(line);
	}
}
