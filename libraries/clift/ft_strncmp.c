/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:07:15 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/25 12:08:52 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cont;

	cont = 0;
	if (n == 0)
		return (0);
	while ((s1[cont] == s2[cont]) && (s1[cont] != '\0' ) && (cont < (n - 1)))
		cont++;
	return ((unsigned char) s1[cont] - (unsigned char) s2[cont]);
}
