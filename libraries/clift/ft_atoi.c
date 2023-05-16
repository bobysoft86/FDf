/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:38:49 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/25 10:11:55 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	tot;
	int	neg;

	tot = 0;
	neg = 1;
	while (ft_isspace(*str))
str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		neg = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		tot = tot * 10 + (*str - 48);
		str++;
	}
	return (tot * neg);
}
