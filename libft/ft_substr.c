/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:22:23 by mjoosten          #+#    #+#             */
/*   Updated: 2021/10/28 13:22:23 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*ret;

	if (!s)
		return (0);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	*str = 0;
	while (start--)
	{
		if (!*s)
			return (str);
		s++;
	}
	ret = str;
	while (len-- && *s)
		*str++ = *s++;
	*str = 0;
	return (ret);
}
