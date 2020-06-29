/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 04:32:29 by glaurent          #+#    #+#             */
/*   Updated: 2020/06/29 21:19:07 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strndup(char *str, int n)
{
	char	*dest;
	int		i;
	int		size;

	dest = NULL;
	size = ft_strlen(str);
	if (!str)
	{
		if (!(dest = malloc(sizeof(char) * (size + 1))))
			return (NULL);
		str = "(null)\0";
	}
	if (!dest)
		if (!(dest = malloc(sizeof(char) * (size + 1))))
			return (NULL);
	i = -1;
	while (++i < n && i < size)
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}

void	ft_less(t_struct *p, char *copy, char c)
{
	int i;
	int	len;

	i = -1;
	len = ft_strlen(copy);
	if (p->minus == TRUE)
	{
		copy ? ft_putstr(copy, p, p->fd) : 1;
		while (++i < (p->width - len))
			ft_putchar(c, p, p->fd);
	}
	else
	{
		while (++i < (p->width - len))
			ft_putchar(c, p, p->fd);
		copy ? ft_putstr(copy, p, p->fd) : 1;
	}
}

void	ft_str(t_struct *p)
{
	char	*copy;
	char	*chaine;
	char	h;

	h = p->zero == TRUE ? '0' : ' ';
	p->precision == -1 ? p->precision = 0 : 1;
	copy = (char *)va_arg(p->ap, void *);
	chaine = ft_strndup(copy,
			p->dot == TRUE ? p->precision : ft_strlen(copy));
	if (p->width != 0)
		ft_less(p, chaine, h);
	else
		ft_putstr(chaine, p, p->fd);
	free(chaine);
}
