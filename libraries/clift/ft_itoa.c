/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:38:43 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/25 12:30:39 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_valor(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	ft_lenv(int num)
{
	int	len;

	len = 0;
	if (num <= 0)
		++len;
	while (num != 0)
	{
		++len;
		num = num / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*total;
	int		len;

	len = ft_lenv (n);
		total = malloc(sizeof (char) * (len + 1));
	if (total == NULL)
		return (NULL);
	total[len] = '\0';
	if (n < 0)
		total[0] = '-';
	else if (n == 0)
		total[0] = '0';
	while (n != 0)
	{
		--len;
		total[len] = ft_valor(n % 10) + '0';
		n = n / 10;
	}
	return (total);
}
