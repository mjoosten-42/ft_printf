/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:30:53 by mjoosten          #+#    #+#             */
/*   Updated: 2024/10/30 16:32:19 by mjoosten       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>

int ft_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));
int ft_fprintf(FILE *stream, const char *format, ...) __attribute__((format(printf, 2, 3)));
int ft_dprintf(int fd, const char *format, ...) __attribute__((format(printf, 2, 3)));

int ft_vprintf(const char *format, va_list ap) __attribute__((format(printf, 1, 0)));
int ft_vfprintf(FILE *stream, const char *format, va_list ap) __attribute__((format(printf, 2, 0)));
int ft_vdprintf(int fd, const char *format, va_list ap) __attribute__((format(printf, 2, 0)));

/*
int ft_xvdprintf(int		 fd,
				 const char *format,
				 va_list	 ap,
				 void (*putc)(void *p, char c),
				 void *p) __attribute__((format(printf, 2, 0)));
*/

#endif
