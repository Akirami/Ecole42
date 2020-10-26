/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 11:46:23 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 11:51:55 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void
	*ft_memalloc(size_t size)
{
	void	*s;
	size_t	i;

	if (!(s = malloc(size)))
		return (s);
	i = 0;
	while (i < size)
	{
		((char *)s)[i] = 0;
		i++;
	}
	return (s);
}
