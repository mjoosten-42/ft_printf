/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:15:55 by mjoosten          #+#    #+#             */
/*   Updated: 2021/11/01 13:48:00 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_puthex_lowercase(unsigned long nb);
static int	ft_puthex_uppercase(unsigned long nb);
static int	ft_putchar(char c);
static int	ft_putstr(char *str);
static int	ft_putnbr(int n);
static int	ft_putnbr_u(unsigned int n);

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
			if (format[i + 1] == 'c')
				ret += ft_putchar(va_arg(ap, int));
			if (format[i + 1] == 's')
				ret += ft_putstr(va_arg(ap, char *));
			if (format[i + 1] == 'p')
			{
				ft_putstr("0x");
				ret += 2 + ft_puthex_lowercase(va_arg(ap, unsigned long));
			}
			if (format[i + 1] == 'd' || format[i + 1] == 'i')
				ret += ft_putnbr(va_arg(ap, int));
			if (format[i + 1] == 'u')
				ret += ft_putnbr_u(va_arg(ap, unsigned int));
			if (format[i + 1] == 'x')
				ret += ft_puthex_lowercase(va_arg(ap, unsigned int));
			if (format[i + 1] == 'X')
				ret += ft_puthex_uppercase(va_arg(ap, unsigned int));
			if (format[i + 1] == '%')
				ret += ft_putchar('%');
			i++;
		}
		else
		{
			ft_putchar(format[i]);
			ret++;
		}
		i++;
	}
	va_end(ap);
	return (ret);
}

static int	ft_puthex_lowercase(unsigned long nb)
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
	ft_putstr_fd(str + i, 1);
	return (ft_strlen(str + i));
}

static int	ft_puthex_uppercase(unsigned long nb)
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

static int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
		write(1, str + i++, 1);
	return (i);
}

static int	ft_putnbr(int n)
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

static int	ft_putnbr_u(unsigned int n)
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
