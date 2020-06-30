/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 00:36:10 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/13 00:36:50 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void	ft_atoi_exit(char *str, int i)
{
	long long	nb;

	nb = 0;
	skip_white(str, &i);
	!str ? exit(0) : 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			ft_printf(2,
				"Minishell: exit: %s: numeric argument required\n", str + 4);
			exit(-1);
		}
		if (nb * 10 + str[i] - '0' <= LLONG_MAX &&
			nb * 10 + str[i] - '0' >= LLONG_MIN)
			nb = nb * 10 + str[i] - '0';
		else
		{
			ft_printf(2,
				"Minishell: exit: %s: numeric argument required\n", str + 4);
			exit(-1);
		}
		++i;
	}
	exit(nb);
}
