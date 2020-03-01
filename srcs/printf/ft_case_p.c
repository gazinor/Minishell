/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:53:58 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/01 18:58:16 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_nbrlen_base(long nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 16;
		size++;
	}
	return (size);
}

void	ft_width_num_p(t_struct *p, long copy, char c)
{
	int		i;

	i = -1;
	if (p->minus == TRUE)
	{
		ft_putstr("0x", p, p->fd);
		(p->precision > p->len) ? ft_display_zero(p, 0) : 1;
		if (p->precision == -1)
			return ;
		ft_putnbr_base((unsigned long long)copy, "0123456789abcdef", p);
		while (++i < (p->width - 2 -
					(p->precision > p->len ? p->precision : p->len)))
			ft_putchar(c, p, p->fd);
	}
	else
	{
		while (++i < (p->width - 2 + (p->precision == -1 ? 1 : 0) -
					(p->precision > p->len ? p->precision : p->len)))
			ft_putchar(c, p, p->fd);
		ft_putstr("0x", p, p->fd);
		(p->precision > p->len) ? ft_display_zero(p, 0) : 1;
		if (p->precision == -1)
			return ;
		ft_putnbr_base((unsigned long long)copy, "0123456789abcdef", p);
	}
}

void	ft_num_p(t_struct *p)
{
	long copy;

	copy = (unsigned long)va_arg(p->ap, void *);
	p->len = ft_nbrlen_base((unsigned long)copy);
	if (p->dot == TRUE)
		p->zero = FALSE;
	else
		p->precision = 0;
	ft_width_num_p(p, copy, p->zero == TRUE ? '0' : ' ');
}
