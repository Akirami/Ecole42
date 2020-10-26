/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:54:56 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:54:56 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list
	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *lst2;
	t_list *new;

	lst2 = f(lst);
	new = lst2;
	while (lst->next)
	{
		lst = lst->next;
		if (!(lst2->next = f(lst)))
		{
			free(lst2->next);
			return (NULL);
		}
		lst2 = lst2->next;
	}
	return (new);
}
