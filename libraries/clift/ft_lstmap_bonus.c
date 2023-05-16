/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:42:07 by roberodr          #+#    #+#             */
/*   Updated: 2023/01/30 10:54:19 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*init;
	t_list	*tmp;
	void	*err;

init = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		err = f (lst->content);
		tmp = ft_lstnew (err);
		if (!tmp)
		{
			del (err);
			ft_lstclear (&init, del);
			return (NULL);
		}
		ft_lstadd_back(&init, tmp);
		lst = lst->next;
	}
	return (init);
}
