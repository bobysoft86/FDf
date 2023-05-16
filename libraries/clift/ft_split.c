/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:23:49 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/31 11:43:51 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

size_t	ft_countto(const char *a, char c)
{
	int		i;
	size_t	lenf;

	lenf = 0;
	i = 0;
	while (a[i] != '\0')
	{
		if (i == 0 && a[i] != c)
			lenf++;
		if (i > 0 && a[i] != c && a[i - 1] == c)
			lenf++;
		i++;
	}
	return (lenf);
}

size_t	ft_sizeword(const char *str, char del, int pos)
{
	int	size;

	size = 0;
	while (str[pos] != del && str[pos])
	{
		pos++;
		size++;
	}
	return (size);
}

char	**ftfree(char **s, size_t contador1)
{
	size_t	i;

	i = 0;
	while (i < contador1)
	{
		free(s[i++]);
	}
	free(s);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	sizemalloc;
	char	**entrada;
	size_t	cont1;
	size_t	cont2;
	size_t	sizetmp;

	cont1 = 0;
	cont2 = 0;
	sizemalloc = ft_countto(s, c);
	entrada = malloc(sizeof(char *) * (sizemalloc +1));
	if (!entrada)
		return (NULL);
	while (cont1 < sizemalloc)
	{
		while (s[cont2] == c)
		cont2++;
	sizetmp = ft_sizeword(s, c, cont2);
	entrada[cont1] = ft_substr(s, cont2, sizetmp);
		if (entrada[cont1] == NULL)
			return (ftfree(entrada, cont1));
	cont2 = cont2 + sizetmp;
	cont1++;
	}
	entrada[sizemalloc] = NULL;
	return (entrada);
}
