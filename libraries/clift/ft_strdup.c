/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:45:56 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/25 11:14:34 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*str;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	str = (char *) malloc(sizeof (char) * len + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
	str[i] = s1[i];
	i++;
	}
str[i] = '\0';
	return (str);
}
