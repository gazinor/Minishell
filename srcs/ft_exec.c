/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 21:54:08 by gaefourn          #+#    #+#             */
/*   Updated: 2020/06/29 23:02:14 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exec(char *str, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i + j] && (str[i + j] != ' ' && str[i + j] != '\t'))
		j++;
	data->exec = ft_substr(str, i, j);
}

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

void	try_exec(t_data *data, char *str)
{
	int		ret;
	char	**envp;
	int		status;

	(void)str;
	envp = ft_split_env(data->env);
	data->pid = fork();
	if (data->pid == 0)
	{
		errno = 0;
		if ((ret = execve(data->binary, data->option, envp)) != 0)
			ft_printf(2, "Minishell: %s: %s\n", data->option[0],
					strerror(errno));
		free_tab(&data->option);
		data->ret = ret;
		exit(ret);
	}
	if (data->pid > 0)
		wait(&status);
	free_tab(&envp);
	free_string(&data->binary);
	data->ret = WEXITSTATUS(status);
}

char	*is_exec(char *str, t_data *data)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = -1;
	get_exec(str, data);
	while (data->paths && data->paths[++i])
	{
		if ((dir = opendir(data->paths[i])) == NULL)
			return (NULL);
		else
		{
			while ((entry = readdir(dir)) != NULL)
				if (ft_strcmp(entry->d_name, data->exec) == 0)
				{
					closedir(dir);
					return (join_n_free(join_n_free(ft_strdup(data->paths[i]),
					ft_strdup("/"), 0), ft_strdup(data->exec), 0));
				}
			closedir(dir);
			free(entry);
			entry = NULL;
		}
	}
	return (NULL);
}
