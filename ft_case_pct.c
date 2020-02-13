/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_pct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:22:23 by glaurent          #+#    #+#             */
/*   Updated: 2019/11/14 05:25:34 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pct(t_struct *p)
{
	int		i;

	i = -1;
	if (p->minus == TRUE)
	{
		ft_putchar('%', p);
		while (++i < p->width - 1)
			ft_putchar(' ', p);
	}
	else
	{
		while (++i < p->width - 1)
			ft_putchar(p->zero == TRUE ? '0' : ' ', p);
		ft_putchar('%', p);
	}
}
