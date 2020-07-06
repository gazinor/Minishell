/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:04:46 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/06 22:21:42 by gaefourn         ###   ########.fr       */
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
		free_string(&data->pwd);
		data->pwd = NULL;
		data->pwd = ft_strdup(str);
		if (j != 0)
			ft_printf(1, "%s\n", data->pwd);
		free_string(&str);
		str = NULL;
		j++;
	}
}

void	ft_cd(char *str, char **here, t_data *data)
{
	int i;

	i = 0;
	errno = 0;
	if (!str && ++data->checkcd)
		str = find_key_value(data->env, "HOME");
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	if (chdir(str + i) == -1)
	{
		str[i] != '\0' ? norme_ft_cd(str, data) :
			ft_printf(2, "cd: %s\n", strerror(errno));
		if (data->here)
		{
			free_string(&data->here);
			where_am_i(data);
		}
		data->check_ret = 1;
	}
	else
		where_am_i(data);
	if (data->checkcd != 0 && !(--data->checkcd))
		free_string(&str);
	(void)here;
}

void	ft_env(t_data *data)
{
	t_env	*copy;

	copy = data->env;
	if (norme_env(data) == -1)
		return ;
	while (copy)
	{
		ft_printf(1, "%s=%s\n", copy->key, copy->value);
		copy = copy->next;
	}
}

void	ft_exit(t_data *data, char *str)
{
	(void)data;
	ft_printf(1, "exit\n");
	if (!str)
		exit(0);
	ft_atoi_exit(str, 4);
}

int		is_builtin(char *str, t_data *data)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if ((ft_norme_builtins1(str, data, i) == 1 ||
		ft_norme_builtins2(str, data, i) == 1 ||
		ft_norme_builtins3(str, data, i) == 1 ||
		ft_norme_builtins4(str, data, i) == 1) && !(data->ret = 0))
		return (1);
	else if (str[i] == '/')
	{
		if (str[i + 1] == '\0' || str[i + 1] == ' ')
		{
			ft_printf(2, "Minishell: /: is a directory\n");
			return (1);
		}
		data->exec = ft_strdup(str);
		data->option = ft_splitv2(str, ' ', data);
		data->binary = ft_strdup(data->option[0]);
		try_exec(data, str);
		return (1);
	}
	return (0);
}
