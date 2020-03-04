/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 04:59:01 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 04:56:30 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		konte_mo(const char *s, char c)
{
	int		kont;

	kont = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			++kont;
			while (*s != c && *s)
				++s;
		}
	}
	return (kont);
}

static	char	*ft_strcdup(const char *s, char c)
{
	char	*dest;
	int		i;
	int		cont;

	i = -1;
	cont = 0;
	while (s[cont] != c && s[cont])
		cont++;
	if (!(dest = malloc(sizeof(char) * (cont + 1))))
		return (NULL);
	while (++i < cont)
		dest[i] = s[i];
	dest[cont] = '\0';
	return (dest);
}

static	void	*ft_erase(char **strs, int i)
{
	while (strs[i])
	{
		free(strs[i]);
		--i;
	}
	free(strs);
	return (NULL);
}

char			**ft_split(const char *s, char c)
{
	char	**strs;
	size_t	len;
	int		i;

	if (!s)
		return (NULL);
	len = konte_mo(s, c);
	if (!(strs = malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			++s;
		while (*s != c && *s)
		{
			if (!(strs[i] = ft_strcdup(s, c)))
				return (ft_erase(strs, i));
			++i;
			while (*s != c && *s)
				++s;
		}
	}
	strs[len] = 0;
	return (strs);
}
