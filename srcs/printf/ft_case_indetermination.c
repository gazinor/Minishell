/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_indetermination.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 06:41:34 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/01 18:48:06 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_indetermination(t_struct *p)
{
	int		i;
	char	copy;

	i = -1;
	copy = p->format[p->i];
	if (p->minus == TRUE)
	{
		ft_putchar(copy ? copy : '\0', p, p->fd);
		while (++i < p->width - 1)
			ft_putchar(' ', p, p->fd);
	}
	else
	{
		while (++i < p->width - 1)
			ft_putchar(p->zero == TRUE ? '0' : ' ', p, p->fd);
		ft_putchar(copy ? copy : '\0', p, p->fd);
	}
}
