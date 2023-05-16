/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:38:02 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/30 10:38:41 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd ('-', fd);
			n = n * -1;
		}
		if (n >= 0 && n <= 9)
			ft_putchar_fd (n + '0', fd);
		if (n > 9)
		{
			ft_putnbr_fd ((n / 10), fd);
			ft_putnbr_fd ((n % 10), fd);
		}
	}
}
