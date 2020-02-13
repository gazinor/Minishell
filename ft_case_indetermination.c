/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_indetermination.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 06:41:34 by glaurent          #+#    #+#             */
/*   Updated: 2019/11/14 06:41:48 by glaurent         ###   ########.fr       */
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
		ft_putchar(copy ? copy : '\0', p);
		while (++i < p->width - 1)
			ft_putchar(' ', p);
	}
	else
	{
		while (++i < p->width - 1)
			ft_putchar(p->zero == TRUE ? '0' : ' ', p);
		ft_putchar(copy ? copy : '\0', p);
	}
}
