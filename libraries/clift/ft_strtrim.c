/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:05:38 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/30 10:07:34 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	final;
	char	*str;

	if (!s1 || !set)
		return (NULL);
		i = 0;
		final = (ft_strlen(s1) -1);
	if (s1[i] == '\0')
		return (ft_strdup(s1));
	while (ft_strchr(set, s1[i]) && i <= final)
	i++;
	if (i > final)
		return (ft_strdup(s1 + final + 1));
	while ((ft_strchr(set, s1[final]) && final >= 0))
	final--;
str = malloc(final - i + 2);
	if (!str)
		return (NULL);
	ft_strlcpy (str, &s1[i], final - i + 2);
	return (str);
}
