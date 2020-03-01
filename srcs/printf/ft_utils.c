/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 23:13:17 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/01 18:57:01 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void	ft_putchar(char c, t_struct *p, int fd)
{
	write(fd, &c, 1);
	++p->count;
}

void	ft_putstr(char *str, t_struct *p, int fd)
{
	int i;

	i = 0;
	if (!str)
	{
		write(fd, "(null)", 6);
		return ;
	}
	while (str[i])
		i++;
	write(fd, str, i);
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
		ft_putchar(base[n], p, p->fd);
}
