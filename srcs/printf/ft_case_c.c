/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 03:41:28 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/01 18:55:09 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_c(t_struct *p)
{
	int		i;
	char	copy;

	i = -1;
	copy = (char)va_arg(p->ap, void*);
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
