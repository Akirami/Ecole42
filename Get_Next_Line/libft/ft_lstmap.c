/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/18 12:13:42 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/18 13:19:32 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
