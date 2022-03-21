/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:30:53 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/21 10:09:53 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);

int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr_base(long nbr, char *base);
int	ft_strlen(const char *s);

#endif