/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:15:55 by mjoosten          #+#    #+#             */
/*   Updated: 2021/11/01 14:11:59 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_percent(char c, va_list ap);
static int	ft_puthex_lwcs(unsigned long nb);
static int	ft_puthex_upcs(unsigned long nb);

int	ft_printf(const char *format, ...)
{
	int		i;
	int		ret;
	va_list	ap;

	if (!format)
		return (0);
	va_start(ap, format);
	i = 0;
	ret = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			ret += ft_percent(format[i + 1], ap);
			i += 2;
		}
		else
		{
			ft_putchar(format[i]);
			ret++;
			i++;
		}
	}
	va_end(ap);
	return (ret);
}

static int	ft_percent(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	if (c == 'p')
		return (ft_putstr("0x") + ft_puthex_lwcs(va_arg(ap, unsigned long)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	if (c == 'u')
		return (ft_putnbr_u(va_arg(ap, unsigned int)));
	if (c == 'x')
		return (ft_puthex_lwcs(va_arg(ap, unsigned int)));
	if (c == 'X')
		return (ft_puthex_upcs(va_arg(ap, unsigned int)));
	if (c == '%')
		return (ft_putchar('%'));
	return (-1);
}

static int	ft_puthex_lwcs(unsigned long nb)
{
	char			str[2 * sizeof(unsigned long) + 1];
	int				i;

	if (!nb)
	{
		ft_putchar('0');
		return (1);
	}
	i = 2 * sizeof(unsigned long);
	while (i--)
	{
		if (nb % 16 < 10)
			str[i] = '0' + nb % 16;
		else
			str[i] = 'a' + nb % 16 - 10;
		nb = nb / 16;
	}
	str[2 * sizeof(unsigned long)] = 0;
	i = 0;
	while (str[i] == '0')
		i++;
	ft_putstr(str + i);
	return (ft_strlen(str + i));
}

static int	ft_puthex_upcs(unsigned long nb)
{
	char			str[2 * sizeof(unsigned long) + 1];
	int				i;

	if (!nb)
	{
		ft_putchar('0');
		return (1);
	}
	i = 2 * sizeof(unsigned long);
	while (i--)
	{
		if (nb % 16 < 10)
			str[i] = '0' + nb % 16;
		else
			str[i] = 'A' + nb % 16 - 10;
		nb = nb / 16;
	}
	str[2 * sizeof(unsigned long)] = 0;
	i = 0;
	while (str[i] == '0')
		i++;
	ft_putstr_fd(str + i, 1);
	return (ft_strlen(str + i));
}
