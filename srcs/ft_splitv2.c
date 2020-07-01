/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:51:33 by gaefourn          #+#    #+#             */
/*   Updated: 2020/07/01 02:55:18 by gaefourn         ###   ########.fr       */
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
	t_s t;

	if (!s)
		return (NULL);
	free_tab(&data->option);
	t.len = konte_mo(s, c);
	if (!(t.strs = malloc(sizeof(char*) * (t.len + 1))))
		return (NULL);
	init_t(&t);
	while (s[t.j])
	{
		if (norme_splitv2v2(&t, c, s) == -1)
			continue ;
		while (s[t.j] != c && s[t.j])
		{
			if (!(t.strs[t.i] = ft_strcdup(s + t.j, c)))
				return (ft_erase(t.strs, t.i));
			t.strs[t.i] = quote_ereaser(t.strs[t.i]);
			++t.i;
			while (s[t.j] != c && s[t.j])
				++t.j;
		}
	}
	t.strs[t.i] = NULL;
	return (t.strs);
}
