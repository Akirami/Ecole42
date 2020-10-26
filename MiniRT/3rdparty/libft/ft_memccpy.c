/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:54:56 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:54:56 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void
	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	i = 0;
	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (len != 0 && src == NULL && dst == NULL)
		return ((void *)0);
	while (i < len)
	{
		dst2[i] = (unsigned char)src2[i];
		if (src2[i] == (unsigned char)c)
			return (dst2 + i + 1);
		i++;
	}
	if ((i > 0) && (src2[i - 1] == c))
		return (dst2 + i);
	return (0);
}
