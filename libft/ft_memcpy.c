/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:21:20 by mjoosten          #+#    #+#             */
/*   Updated: 2021/10/28 13:21:20 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	char	*dest;

	dest = (char *)dst;
	if (!(dst || src))
		return (0);
	while (n--)
		*dest++ = *(char *)src++;
	return (dst);
}
