/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:21:43 by mjoosten          #+#    #+#             */
/*   Updated: 2021/10/28 13:21:43 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_wordcount(char const *s, char c);
static int	ft_wordlength(char const *s, char c);
static int	ft_wordcpy(char **strs, char const *s, char c);
static int	ft_freestrs(char **strs, int i);

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (0);
	if (!c)
	{
		strs = malloc(1);
		*strs = 0;
		return (strs);
	}
	while (*s == c)
		s++;
	strs = (char **)malloc((ft_wordcount(s, c) + 1) * sizeof(char **));
	if (!strs)
		return (0);
	if (ft_wordcpy(strs, s, c))
		return (0);
	*(strs + ft_wordcount(s, c)) = 0;
	return (strs);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		while (*s == c)
			s++;
		i++;
	}
	return (i);
}

static int	ft_wordlength(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

static int	ft_wordcpy(char **strs, char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	while (*s)
	{
		*(strs + i) = (char *)malloc(ft_wordlength(s, c) + 1);
		if (ft_freestrs(strs, i))
			return (1);
		j = 0;
		while (*s && *s != c)
			*(*(strs + i) + j++) = *s++;
		*(*(strs + i) + j) = 0;
		while (*s == c)
			s++;
		i++;
	}
	return (0);
}

static int	ft_freestrs(char **strs, int i)
{
	if (!(*(strs + i)))
	{
		i++;
		while (i--)
			free(*(strs + i));
		free(strs);
		return (1);
	}
	return (0);
}
