/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:21:22 by mjoosten          #+#    #+#             */
/*   Updated: 2021/11/01 10:54:21 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static int	ft_str_overlap(char *dst, char*src, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*source;

	dest = (char *)dst;
	source = (char *)src;
	if (!(dst || src))
		return (0);
	if (ft_str_overlap(dest, source, len))
		while (len--)
			*(dest + len) = *(source + len);
	else
		while (len--)
			*dest++ = *source++;
	return (dst);
}

static int	ft_str_overlap(char *dst, char *src, size_t len)
{
	while (len--)
	{
		if (dst == src)
			return (1);
		src++;
	}
	return (0);
}
