/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:54:56 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:54:56 by emassard         ###   ########lyon.fr   */
/*                                                                            */
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
