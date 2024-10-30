/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:43:56 by mjoosten          #+#    #+#             */
/*   Updated: 2024/10/30 16:32:48 by mjoosten       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	int ret = ft_vprintf(format, ap);
	va_end(ap);

	return ret;
}
