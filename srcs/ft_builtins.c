/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:04:46 by gaefourn          #+#    #+#             */
/*   Updated: 2020/02/14 03:17:10 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char *line)
{
	char *str;
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\0')
		ft_printf("pwd: too many arguments\n");
	else
	{
		str = NULL;
		str = getcwd(str, 0);
		ft_printf("%s\n", str);
		free(str);
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
	while(data->env)
	{
		ft_printf("%s=%s\n", data->env->key, data->env->value);
		data->env = data->env->next;
	}
}

int		is_builtin(char *str, t_data *data)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == 'c' && str[i + 1] == 'd' && (str[i + 2] == ' ' ||
				str[i + 2] == '\t' || str[i + 2] == '\0'))
		ft_cd(str + i + 2, &data->here);
	else if (str[i] == 'p' && str[i + 1] == 'w' &&
			str[i + 2] == 'd' && (str[i + 3] == ' ' ||
				str[i + 3] == '\t' || str[i + 3] == '\0'))
		ft_pwd(str + 3);
	else if (str[i] == 'e' && str[i + 1] == 'n' && str[i + 3] == 'v' &&
			(str[i + 4] == ' ' ||
				str[i + 4] == '\t' || str[i + 4] == '\0'))
		ft_env(data);
	else
		return (0);
	return (1);
}
