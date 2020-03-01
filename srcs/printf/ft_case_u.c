/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 02:24:16 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/01 18:52:30 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_norme(t_struct *p, unsigned int copy, char c)
{
	int	i;

	i = -1;
	while (++i < (p->width + (p->precision == 0 && copy == 0 &&
	p->dot == TRUE ? 1 : 0) - (p->precision > p->len ? p->precision : p->len)))
		ft_putchar(c, p, p->fd);
	if (p->len == 1 && p->width != 0 && p->precision == -1 &&
			i <= p->width && p->dot == TRUE)
		ft_putchar(' ', p, p->fd);
	if (p->precision > p->len)
		ft_display_zero(p, copy == 0 ? 1 : 0);
	if (copy == 0 && p->dot == TRUE)
	{
		p->precision == 1 ? ft_putchar('0', p, p->fd) : 1;
		return ;
	}
	ft_putnbr_base((unsigned int)copy, "0123456789", p);
}

void			ft_width_num_u(t_struct *p, unsigned int copy, char c, int i)
{
	if (p->minus == TRUE)
	{
		if (p->precision > p->len)
			ft_display_zero(p, copy == 0 ? 1 : 0);
		if (copy == 0 && p->dot == TRUE)
		{
			if (p->width == 0)
			{
				p->precision == 1 ? ft_putchar('0', p, p->fd) : 1;
				return ;
			}
			p->precision == 1 ? ft_putchar('0', p, p->fd) : 1;
		}
		if (!(copy == 0 && p->dot == TRUE && p->width != 0))
			ft_putnbr_base((unsigned int)copy, "0123456789", p);
		else
			p->len = 0;
		while (++i < (p->width -
					(p->precision > p->len ? p->precision : p->len)))
			ft_putchar(c, p, p->fd);
	}
	else
		ft_norme(p, copy, c);
}

void			ft_num_u(t_struct *p)
{
	int				i;
	unsigned int	copy;

	i = -1;
	copy = (unsigned int)va_arg(p->ap, void *);
	p->len = ft_nbrlen(copy);
	if (p->dot == TRUE)
		p->zero = FALSE;
	ft_width_num_u(p, copy, p->zero == TRUE ? '0' : ' ', i);
}
