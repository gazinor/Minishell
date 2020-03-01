/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 01:30:51 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/01 18:43:32 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_set_find(char c)
{
	if (c == 'c' || c == 'd' || c == 'i' || c == 's' || c == 'x' || c == 'X' ||
			c == 'u' || c == 'p' || c == '%')
		return (0);
	else if (c != 'c' && c != 'd' && c != 'i' && c != 's' && c != 'x' &&
			c != 'X' && c != 'u' && c != 'p' && c != '%' && c != '-' &&
			c != '*' && c != '.' && !(c >= '0' && c <= '9'))
		return (0);
	else if (c == '\0')
		return (-1);
	return (1);
}

void	ft_check_again_xd(t_struct *p)
{
	if (p->format[p->i] == '*')
	{
		if (p->format[p->i - 1] == '.')
		{
			if ((p->precision = (int)va_arg(p->ap, void *)) < 0)
				p->dot = FALSE;
			p->precision = p->precision <= 0 ? -1 : p->precision;
		}
		else if ((p->width = (int)va_arg(p->ap, void *)) < 0)
		{
			p->width = -p->width;
			p->minus = TRUE;
		}
	}
	else if (p->format[p->i] == '-')
		p->minus = TRUE;
	else if (p->format[p->i] == '0')
		p->zero = TRUE;
	else if (p->format[p->i] == '.')
	{
		p->dot = TRUE;
		p->precision = ft_atoi(p);
	}
	else if (p->format[p->i] >= '1' && p->format[p->i] <= '9')
		p->width = ft_atoi(p);
}

void	ft_look(t_struct *p)
{
	while (++p->i < p->total &&
			(ft_set_find(p->format[p->i]) == 1))
		ft_check_again_xd(p);
	if (p->minus == TRUE)
		p->zero = FALSE;
	if (p->format[p->i] == 'c')
		ft_c(p);
	else if (p->format[p->i] == 's')
		ft_str(p);
	else if (p->format[p->i] == 'd' || p->format[p->i] == 'i')
		ft_num(p);
	else if (p->format[p->i] == 'u')
		ft_num_u(p);
	else if (p->format[p->i] == 'x')
		ft_num_x(p);
	else if (p->format[p->i] == 'X')
		ft_num_x_big(p);
	else if (p->format[p->i] == '%')
		ft_pct(p);
	else if (p->format[p->i] == 'p')
		ft_num_p(p);
	else if (p->format[p->i] == '\0')
		--p->i;
	else
		ft_indetermination(p);
}

int		ft_printf(int fd, const char *format, ...)
{
	t_struct	p;

	ft_init_p(&p);
	p.fd = fd;
	p.format = format;
	va_start(p.ap, format);
	while (p.format[p.total])
		++p.total;
	while (p.format[p.i])
	{
		if (p.format[p.i] == '%')
		{
			ft_reset_flags(&p);
			ft_look(&p);
		}
		else
			ft_putchar(p.format[p.i], &p, p.fd);
		++p.i;
	}
	va_end(p.ap);
	return (p.count);
}
