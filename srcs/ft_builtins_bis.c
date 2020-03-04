/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:21:06 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/04 20:31:11 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_norme_builtins1(char *str, t_data *data, int i)
{
	if (str[i] == 'c' && str[i + 1] == 'd' && (str[i + 2] == ' ' ||
				str[i + 2] == '\t' || str[i + 2] == '\0'))
	{
		if (where_am_i() != NULL)
			ft_cd(str + i + 2, &data->here, data);
		else if (str[i + 2] == ' ' && str[i + 3] == '.' && (str[i + 4] == '\0'
					|| str[i + 4] == ' '))
		{
			if (data->pwd == data->here)
				ft_cd(data->pwd, &data->here, data);
			else
				ft_cd(ft_strjoin(ft_strjoin(data->pwd, "/"), data->here),
						&data->here, data);
			//OMG FAUT FREE CETTE MERDE, MAIS COMMENT FAIRE ????????
		}
		else
			ft_cd(data->pwd, &data->here, data);
		return (1);
	}
	return (0);
}

int		ft_norme_builtins2(char *str, t_data *data, int i)
{
	if (str[i] == 'p' && str[i + 1] == 'w' &&
			str[i + 2] == 'd' && (str[i + 3] == ' ' ||
				str[i + 3] == '\t' || str[i + 3] == '\0'))
	{
		if (where_am_i() != NULL)
			ft_pwd(str + 3, data);
		else
		{
			if (data->pwd == data->here)
				ft_printf(1, "%s\n", data->pwd);
			else
				ft_printf(1, "%s/%s\n", data->pwd, data->here);
		}
		return (1);
	}
	else if (str[i] == 'e' && str[i + 1] == 'n' && str[i + 2] == 'v' &&
			(str[i + 3] == ' ' ||
			str[i + 3] == '\t' || str[i + 3] == '\0'))
	{
		ft_env(data);
		return (1);
	}
	return (0);
}

int		ft_norme_builtins3(char *str, t_data *data, int i)
{
	if (str[i] == 'e' && str[i + 1] == 'x' && str[i + 2] == 'i' &&
			str[i + 3] == 't' && (str[i + 4] == ' ' ||
				str[i + 4] == '\t' || str[i + 4] == '\0'))
	{
		ft_exit(data);
		return (1);
	}
	else if (str[i] == 'e' && str[i + 1] == 'x' && str[i + 2] == 'p' &&
			str[i + 3] == 'o' && str[i + 4] == 'r' && str[i + 5] == 't' &&
			(str[i + 6] == ' ' || str[i + 6] == '\t' ||
			str[i + 6] == '\0'))
	{
		ft_export(str, &data->env, data);
		return (1);
	}
	else if (str[i] == 'u' && str[i + 1] == 'n' && str[i + 2] == 's' &&
			str[i + 3] == 'e' && str[i + 4] == 't' && (str[i + 5] == ' ' ||
				str[i + 5] == '\t' || str[i + 5] == '\0'))
	{
		ft_unset(str, data);
		return (1);
	}
	return (0);
}

int		ft_norme_builtins4(char *str, t_data *data, int i)
{
	if (str[i] == 'e' && str[i + 1] == 'c' && str[i + 2] == 'h' &&
			str[i + 3] == 'o' && (str[i + 4] == ' ' ||
				str[i + 4] == '\t' || str[i + 4] == '\0'))
	{
		ft_echo(str, data);
		return (1);
	}
	else if (str[i] == '.' && (str[i + 1] == '/'))
	{
		data->binary = ft_strdup(str);
		data->exec = data->binary;
		data->option = ft_split(str, ' ');
		try_exec(data, str);
		return (1);
	}
	return (0);
}
