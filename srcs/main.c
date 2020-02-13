/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 05:42:18 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/13 10:57:53 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "Get_Next_Line/get_next_line.h"
#include "../includes/minishell.h"

char    *where_am_i(void)
{
	char	*str;
	char	*here;
	int		i;

	str = NULL;
	str = getcwd(str, 0);
	i = ft_strlen(str) - 1;
	while (str[i] != '/' && str[i])
		i--;
	here = ft_strdup(str + i + 1);
	return (here);
}

int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
void	skip_white(char **)
{
	
}

void	skip_not_white(char **)
{
	
}
*/
void	ft_pwd(void)
{
	char *str;

	str = NULL;
	str = getcwd(str, 0);
	ft_printf("%s\n", str);
	free(str);
}


int		check_char(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		++i;
	if (str[i] == '\n')
		return (1);
	return (0);
}

void	ft_cd(char *str, char **here)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	chdir(str + i);
	free(*here);
	*here = NULL;
	*here = where_am_i();
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

char	*find_key_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**get_paths(t_data *data)
{
	char	*not_split;

	if ((not_split = find_key_value(data->env, "PATH")) == NULL)
		ft_printf("Ah ouais bah j'ai pas find le PATH ta mere.\n");
	return (ft_split(not_split, ':'));
}

void	try_exec(t_data *data, char **envp)
{
	int		ret;

	data->pid = fork();
	if (data->pid == 0)
	{
		errno = 0;
		if ((ret = execve(data->binary, data->option, envp)) != 0)
			ft_printf("Mon premier shell: %s: %s\n", strerror(errno), data->exec);
		exit(ret);
	}
	if (data->pid > 0)
		wait(0);
}

char	*is_exec(char *str, t_data *data)
{
	DIR				*dir;
	struct	dirent	*entry;
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
					return (ft_strjoin(ft_strjoin(data->paths[i], "/"), data->exec));
			closedir(dir);
		}
	}
	return (NULL);
}

int		is_builtin(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == 'c' && str[i + 1] == 'd' && (str[i + 2] == ' ' || str[i + 2] == '\t' || str[i + 2] == '\0'))
		ft_cd(str + i + 2, &data->here);
	else if (str[i] == 'p' && str[i + 1] == 'w' &&
			str[i + 2] == 'd' && (str[i + 3] == ' ' || str[i + 3] == '\t' || str[i + 3] == '\0'))
		ft_pwd();
	else
		return (0);
	return (1);
}

void	init_env(t_env **env, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		if (!(*env = malloc(sizeof(t_env))))
			return ;
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				(*env)->key = ft_substr(envp[i], 0, j);
				(*env)->value = ft_strdup(envp[i] + j + 1);
				env = &(*env)->next;
				break;
			}
			j++;
		}
		i++;
	}
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
	while ((ret = get_next_line(0, &line)) > 0)
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
