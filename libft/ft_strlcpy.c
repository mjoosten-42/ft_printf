/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:22:03 by mjoosten          #+#    #+#             */
/*   Updated: 2021/10/28 13:22:03 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	len;

	len = ft_strlen(src);
	if (!dstsize)
		return (len);
	while (*src && --dstsize)
		*dst++ = *src++;
	*dst = 0;
	return (len);
}
