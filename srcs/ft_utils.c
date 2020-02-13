/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:09:28 by gaefourn          #+#    #+#             */
/*   Updated: 2020/02/14 00:30:24 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*where_am_i(void)
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

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		++i;
	if (str[i] == '\n')
		return (1);
	return (0);
}
