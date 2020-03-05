/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:04:46 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/05 19:37:06 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char *line, t_data *data)
{
	char		*str;
	static int	j = 0;
	int			i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	str = NULL;
	str = getcwd(str, 0);
	if (str != NULL)
	{
		free(data->pwd);
		data->pwd = NULL;
		data->pwd = ft_strdup(str);
		if (j != 0)
			ft_printf(1, "%s\n", data->pwd);
		free(str);
		str = NULL;
		j++;
	}
}

void	ft_cd(char *str, char **here, t_data *data)
{
	int i;

	i = 0;
	errno = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (chdir(str + i) == -1)
	{
		if (str[i] != '\0')
			ft_printf(2, "cd: %s: %s\n", strerror(errno), *ft_split(str, ' '));
		else
			ft_printf(2, "cd: %s\n", strerror(errno));
		if (data->here)
		{
			free(data->here);
			data->here = NULL;
		}
		data->ret = 1;
	}
	else
		where_am_i(data);
	(void)here;
}

void	ft_env(t_data *data)
{
	t_env	*copy;

	copy = data->env;
	while (copy)
	{
		ft_printf(1, "%s=%s\n", copy->key, copy->value);
		copy = copy->next;
	}
}

void	ft_exit(t_data *data)
{
	(void)data;
	ft_printf(1, "exit\n");
	exit(0);
}

int		is_builtin(char *str, t_data *data)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (ft_norme_builtins1(str, data, i) == 1 ||
		ft_norme_builtins2(str, data, i) == 1 ||
		ft_norme_builtins3(str, data, i) == 1 ||
		ft_norme_builtins4(str, data, i) == 1)
		return (1);
	else if (str[i] == '/')
	{
		if (str[i + 1] == '\0' || str[i + 1] == ' ')
		{
			ft_printf(2, "Minishell: /: is a directory\n");
			return (1);
		}
		data->binary = ft_strdup(str);
		data->exec = data->binary;
		data->option = ft_split(str, ' ');
		try_exec(data, str);
		return (1);
	}
	data->ret = 0;
	return (0);
}
