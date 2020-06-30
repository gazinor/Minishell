/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:51:33 by gaefourn          #+#    #+#             */
/*   Updated: 2020/06/30 19:21:16 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		konte_mo(const char *s, char c)
{
	int		kont;
	int		i;
	kont = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			skip_char((char *)s, &i, (s[i]));
			++kont;
			++i;
			continue ;
		}
		while (s[i] == c && s[i])
				++i;
		while (s[i] != c && s[i])
		{
			++kont;
			while (s[i] != c && s[i])
				++i;
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
char			**ft_splitv2(const char *s, char c, t_data *data)
{
	char	**strs;
	int		len;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	free_tab(&data->option);
	len = konte_mo(s, c);
	if (!(strs = malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	printf("str : |%s|\n", s);
	while (s[j])
	{
		while (s[j] == c && s[j])
			++j;
		if ((s[j] == '"' || s[j] == '\'') && ++j)
		{
			k = j - 1;
			skip_char((char *)s, &j, s[j - 1]);
			while (s[j] && s[++j] != c && s[j])
				if ((s[j] == '"' || s[j] == '\'') && s[j + 1])
				{
					++j;
					skip_char((char *)s, &j, s[j - 1]);
				}
			strs[i] = ft_substr(s, k, (j - k));
			strs[i] = quote_ereaser(strs[i]);
			++i;
			if (s[j])
				++j;
			continue ;
		}
		while (s[j] != c && s[j])
		{
			if (!(strs[i] = ft_strcdup(s + j, c)))
				return (ft_erase(strs, i));
			++i;
			while (s[j] != c && s[j])
				++j;
		}
	}
	strs[i] = NULL;
	i = -1;
	while (strs[++i])
		printf("%d : |%s|\n", i, strs[i]);
	return (strs);
}
