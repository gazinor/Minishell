/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 23:13:17 by glaurent          #+#    #+#             */
/*   Updated: 2019/11/14 11:21:31 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void	ft_putchar(char c, t_struct *p)
{
	write(1, &c, 1);
	++p->count;
}

void	ft_putstr(char *str, t_struct *p)
{
	int i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return ;
	}
	while (str[i])
		i++;
	write(1, str, i);
	p->count += i;
}

void	ft_putnbr_base(unsigned long long n, char *base, t_struct *p)
{
	unsigned long long	i;

	i = 0;
	while (base[i])
		i++;
	if (n >= i)
	{
		ft_putnbr_base(n / i, base, p);
		ft_putnbr_base(n % i, base, p);
	}
	else
		ft_putchar(base[n], p);
}
