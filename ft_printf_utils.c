/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:01:53 by mjoosten          #+#    #+#             */
/*   Updated: 2021/11/01 14:12:21 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
		write(1, str + i++, 1);
	return (i);
}

int	ft_putnbr(int n)
{
	char	c;
	int		i;

	i = 0;
	if (n / 10)
		i = ft_putnbr(n / 10);
	else if (n < 0)
	{
		write(1, "-", 1);
		i++;
	}
	if (n > 0)
		c = '0' + n % 10;
	else
		c = '0' - (n % 10);
	write(1, &c, 1);
	return (i + 1);
}

int	ft_putnbr_u(unsigned int n)
{
	char	c;
	int		i;

	i = 0;
	if (n / 10)
		i = ft_putnbr(n / 10);
	c = '0' + n % 10;
	write(1, &c, 1);
	return (i + 1);
}
