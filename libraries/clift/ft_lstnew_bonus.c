/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:30:23 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/30 10:43:38 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*pr;

pr = ((t_list *) malloc(sizeof (t_list)));
	if (pr == NULL)
		return (NULL);
pr -> content = content;
pr -> next = NULL;
	return (pr);
}
