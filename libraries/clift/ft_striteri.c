/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:42:40 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/27 17:24:20 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t			len_s;
	unsigned int	i;

	i = 0;
	len_s = ft_strlen(s);
	while (i < len_s)
	{
		f(i, &s[i]);
		i++;
	}
}
