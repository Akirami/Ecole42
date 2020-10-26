/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:01 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:01 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void
	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	const char		*src2;

	i = 0;
	dst2 = (unsigned char *)dst;
	src2 = (const char *)src;
	if (len != 0 && src == NULL && dst == NULL)
		return ((void *)0);
	while (i < len)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}
