/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:04:46 by gaefourn          #+#    #+#             */
/*   Updated: 2020/02/18 21:30:19 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char *line, t_data *data)
{
	char *str;
	static int j = 0;
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	str = NULL;
	str = getcwd(str, 0);
	if (str != NULL)
	{
		free(data->pwd);
		data->pwd = ft_strdup(str);
		if (j != 0)
			ft_printf("%s\n", data->pwd);
		free(str);
		j++;
	}
}

void	ft_cd(char *str, char **here)
{
	int i;

	i = 0;
	errno = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (chdir(str + i) == -1)
		ft_printf("cd: %s: %s\n", strerror(errno), *ft_split(str, ' '));
	else
	{
		free(*here);
		*here = NULL;
		*here = where_am_i();
	}
}

void	ft_env(t_data *data)
{
	t_env	*copy;

	copy = data->env;
	while(copy)
	{
		ft_printf("%s=%s\n", copy->key, copy->value);
		copy = copy->next;
	}
}

void	ft_exit(t_data *data)
{
	(void)data;
	ft_printf("exit\n");
	exit(0);
}

int		is_builtin(char *str, t_data *data)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == 'c' && str[i + 1] == 'd' && (str[i + 2] == ' ' ||
				str[i + 2] == '\t' || str[i + 2] == '\0'))
	{
		if (where_am_i() != NULL)
			ft_cd(str + i + 2, &data->here);
		else if (str[i + 2] == ' ' && str[i + 3] == '.' && (str[i + 4] == '\0'
					|| str[i + 4] == ' '))
		{
			if (data->pwd == data->here)
				ft_cd(data->pwd, &data->here);
			else
				ft_cd(ft_strjoin(ft_strjoin(data->pwd, "/"), data->here),
					&data->here);
		}
		else
			ft_cd(data->pwd, &data->here);
	}
	else if (str[i] == 'p' && str[i + 1] == 'w' &&
			str[i + 2] == 'd' && (str[i + 3] == ' ' ||
				str[i + 3] == '\t' || str[i + 3] == '\0'))
	{
		if (where_am_i() != NULL)
			ft_pwd(str + 3, data);
		else
		{
			if (data->pwd == data->here)
				ft_printf("%s\n", data->pwd);
			else
				ft_printf("%s/%s\n", data->pwd, data->here);
		}
	}
	else if (str[i] == 'e' && str[i + 1] == 'n' && str[i + 2] == 'v' &&
			(str[i + 3] == ' ' ||
				str[i + 3] == '\t' || str[i + 3] == '\0'))
		ft_env(data);
	else if (str[i] == 'e' && str[i + 1] == 'x' && str[i + 2] == 'i' &&
			str[i + 3] == 't' && (str[i + 4] == ' ' ||
				str[i + 4] == '\t' || str[i + 4] == '\0'))
		ft_exit(data);
	else if (str[i] == 'e' && str[i + 1] == 'x' && str[i + 2] == 'p' &&
			str[i + 3] == 'o' && str[i + 4] == 'r' && str[i + 5] == 't' &&
			(str[i + 6] == ' ' || str[i + 6] == '\t' ||
			 str[i + 6] == '\0'))
		ft_export(str, &data->env, data);
	else if (str[i] == 'u' && str[i + 1] == 'n' && str[i + 2] == 's' &&
			str[i + 3] == 'e' && str[i + 4] == 't' && (str[i + 5] == ' ' ||
			str[i + 5] == '\t' || str[i + 5] == '\0'))
		ft_unset(str, data);
	else if (str[i] == 'e' && str[i + 1] == 'c' && str[i + 2] == 'h' &&
			str[i + 3] == 'o' && (str[i + 4] == ' ' ||
				str[i + 4] == '\t' || str[i + 4] == '\0'))
		ft_echo(str, data);
	else
		return (0);
	return (1);
}
