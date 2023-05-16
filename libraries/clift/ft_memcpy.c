/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:16:39 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/25 11:06:30 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dst, const void	*src, size_t	n)
{
	size_t	p;

	p = 0;
	if (dst == src)
		return (dst);
	while (p < n)
	{
	((unsigned char *) dst)[p] = ((unsigned char *) src)[p];
		p++;
	}
	return (dst);
}
