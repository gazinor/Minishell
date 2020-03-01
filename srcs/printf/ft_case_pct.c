/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_pct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:22:23 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/01 18:50:18 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pct(t_struct *p)
{
	int		i;

	i = -1;
	if (p->minus == TRUE)
	{
		ft_putchar('%', p, p->fd);
		while (++i < p->width - 1)
			ft_putchar(' ', p, p->fd);
	}
	else
	{
		while (++i < p->width - 1)
			ft_putchar(p->zero == TRUE ? '0' : ' ', p, p->fd);
		ft_putchar('%', p, p->fd);
	}
}
