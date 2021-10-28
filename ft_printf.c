/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:15:55 by mjoosten          #+#    #+#             */
/*   Updated: 2021/10/28 13:18:23 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdarg.h>

static void	ft_percent(char **format);

int	ft_printf(const char *format, ...)
{
	int	i;

	if (!format)
		return (0);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_percent(&format);
		}
		else
			ft_putchar_fd(format[i], 1);
		i++;
	}
	return (i);
}

static void	ft_percent(char **format)
{
	if (*(format + 1) == 'c')
		va_arg
}
