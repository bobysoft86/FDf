/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:21:23 by roberodr          #+#    #+#             */
/*   Updated: 2023/05/05 12:22:52 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	ls1;
	size_t	ls2;
	int		i;
	char	*total;

	if (s1 && s2)
	{
		ls1 = ft_strlen(s1);
		ls2 = ft_strlen(s2);
		total = malloc(sizeof(char) * (ls1 + ls2 + 1));
		if (total == NULL)
			return (NULL);
		i = -1;
		while (s1[++i] != '\0')
			total[i] = s1[i];
		i = -1;
		while (s2[++i] != '\0')
			total[ls1++] = s2[i];
		total[ls1] = '\0';
		return (total);
	}
	return (NULL);
}
