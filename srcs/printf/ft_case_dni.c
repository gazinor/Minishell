/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_dni.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 02:28:59 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/01 18:57:12 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_display_zero(t_struct *p, int signe)
{
	int	i;

	i = -1;
	while (++i < p->precision - p->len + signe)
		ft_putchar('0', p, p->fd);
}

static void		ft_norme(t_struct *p, long copy, char c, int i)
{
	long	c_copy;

	c_copy = copy < 0 ? -copy : copy;
	if (p->zero == TRUE)
		copy < 0 ? ft_putchar('-', p, p->fd) : 1;
	while (++i < (p->width - (copy < 0 && p->precision >= p->len ? 1 : 0) +
				(p->precision == 0 && copy == 0 && p->dot == TRUE ? 1 : 0) -
				(p->precision > p->len ? p->precision : p->len)))
		ft_putchar(c, p, p->fd);
	if (p->len == 1 && p->width != 0 && p->precision == -1 &&
			i <= p->width && p->dot == TRUE)
		ft_putchar(' ', p, p->fd);
	if (p->zero == FALSE)
		copy < 0 ? ft_putchar('-', p, p->fd) : 1;
	if (copy < 0 && p->precision == p->len)
		ft_putchar('0', p, p->fd);
	if (p->precision > p->len)
		ft_display_zero(p, copy <= 0 ? 1 : 0);
	if (copy == 0 && p->dot == TRUE)
	{
		p->precision == 1 ? ft_putchar('0', p, p->fd) : 1;
		return ;
	}
	ft_putnbr_base((long)c_copy, "0123456789", p);
}

static void		ft_norme_again_xd(t_struct *p, long copy, long c_copy)
{
	c_copy = copy < 0 ? -copy : copy;
	if (copy < 0 && p->precision == p->len)
		ft_putchar('0', p, p->fd);
	if (p->precision > p->len)
		ft_display_zero(p, copy <= 0 ? 1 : 0);
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
		ft_putnbr_base((long)c_copy, "0123456789", p);
	else
		p->precision <= 0 &&
			p->precision >= p->len ? ft_putchar('0', p, p->fd) : 1;
}

void			ft_width_num(t_struct *p, long copy, char c, int i)
{
	long	c_copy;

	c_copy = copy < 0 ? -copy : copy;
	if (p->minus == TRUE)
	{
		copy < 0 ? ft_putchar('-', p, p->fd) : 1;
		ft_norme_again_xd(p, copy, c_copy);
		if (copy == 0 && p->dot == TRUE && p->width != 0)
			p->len = 0;
		while (++i < (p->width - (copy < 0 && p->precision >= p->len ? 1 : 0) -
					(p->precision > p->len ? p->precision : p->len)))
			ft_putchar(c, p, p->fd);
	}
	else
		ft_norme(p, copy, c, i);
}

void			ft_num(t_struct *p)
{
	int	i;
	int copy;

	i = -1;
	copy = (int)va_arg(p->ap, void *);
	p->len = ft_nbrlen(copy);
	if (p->dot == TRUE)
		p->zero = FALSE;
	ft_width_num(p, copy, p->zero == TRUE ? '0' : ' ', i);
}
