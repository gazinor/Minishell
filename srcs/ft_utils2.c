/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:26:19 by glaurent          #+#    #+#             */
/*   Updated: 2020/06/25 15:15:59 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_ereaser(char *str, char c)
{
	int 	i;
	int		j;
	char	*cpy;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			j++;
		i++;
	}
	if (!(cpy = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			cpy[j] = str[i];
			j++;
		}
		i++;
	}
	cpy[j] = '\0';
	free_string(&str);
	return (cpy);
}
