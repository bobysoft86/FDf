/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:48:49 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/25 11:45:31 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ldst;
	size_t	ldst2;
	size_t	lsrc;
	size_t	i;

	i = 0;
	ldst2 = ft_strlen(dst);
	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (dstsize < 1)
		return (lsrc);
	while (i < lsrc && ldst < dstsize -1)
	{
		dst[ldst] = src[i];
		ldst++;
		i++;
	}
	dst[ldst] = '\0';
	if (dstsize < ldst2)
		return (lsrc + dstsize);
	else
		return (ldst2 + lsrc);
}
