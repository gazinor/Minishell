/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:04:46 by gaefourn          #+#    #+#             */
/*   Updated: 2020/02/13 22:45:15 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char *str;

	str = NULL;
	str = getcwd(str, 0);
	ft_printf("%s\n", str);
	free(str);
}

void	ft_cd(char *str, char **here)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	chdir(str + i);
	free(*here);
	*here = NULL;
	*here = where_am_i();
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
		ft_pwd();
	else
		return (0);
	return (1);
}
