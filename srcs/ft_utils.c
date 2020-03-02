/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:09:28 by gaefourn          #+#    #+#             */
/*   Updated: 2020/03/02 03:30:19 by gaefourn         ###   ########.fr       */
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
	if (str)
	{
		i = ft_strlen(str) - 1;
		while (str[i] != '/' && str[i])
			i--;
		here = ft_strdup(str + i + 1);
		free(str);
		return (here);
	}
	return (NULL);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_strncmp(const char *s1, const char *s2, int n)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		check_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != c)
		++i;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	**ft_split_env(t_env *env)
{
	int		i;
	char	**copy;
	t_env	*head;

	head = env;
	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	if (!(copy = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (head)
	{
		copy[i] = ft_strdup(ft_strjoin(ft_strjoin(head->key, "="),
					head->value));
		i++;
		head = head->next;
	}
	copy[i] = 0;
	return (copy);
}
