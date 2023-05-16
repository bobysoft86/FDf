/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:17:53 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/25 12:11:53 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	end;

	end = ft_strlen(s);
	while (end >= 0)
	{
		if (s[end] == (unsigned char)c)
			return ((char *) s + end);
		end--;
	}
	return (NULL);
}
