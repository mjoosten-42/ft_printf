/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:01:53 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/21 10:09:31 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	if (!str)
		return (ft_putstr("(null)"));
	return (write(1, str, ft_strlen(str)));
}

int	ft_putnbr_base(long nbr, char *base)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(base);
	if (nbr / size)
		i = ft_putnbr_base(nbr / size, base);
	else if (nbr < 0)
		i += ft_putchar('-');
	if (nbr > 0)
		return (i + ft_putchar(base[nbr % size]));
	return (i + ft_putchar(base[-nbr % size]));
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
