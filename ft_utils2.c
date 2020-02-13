/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 01:37:47 by glaurent          #+#    #+#             */
/*   Updated: 2019/11/18 22:58:10 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_reset_flags(t_struct *p)
{
	p->dot = FALSE;
	p->minus = FALSE;
	p->zero = FALSE;
	p->precision = 0;
	p->width = 0;
	p->len = 0;
}

void	ft_init_p(t_struct *p)
{
	p->format = NULL;
	p->count = 0;
	p->i = 0;
	p->total = 0;
}

int		ft_atoi(t_struct *p)
{
	int nb;

	nb = 0;
	if (p->format[p->i] == '.' && !(p->format[++p->i] >= '0' &&
				p->format[p->i] <= '9'))
	{
		--p->i;
		return (-1);
	}
	while (p->format[p->i] >= '0' && p->format[p->i] <= '9')
	{
		nb = nb * 10 + (p->format[p->i] - '0');
		++p->i;
	}
	--p->i;
	return (nb);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (6);
	while (str[i])
		i++;
	return (i);
}

int		ft_nbrlen(long nb)
{
	int size;

	size = 0;
	if (nb == 0)
		return (1);
	else if (nb < 0)
		size++;
	while (nb != 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}
