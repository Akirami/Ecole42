/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:00 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:00 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void
	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*str2;

	str2 = (unsigned char *)str;
	i = 0;
	while (i++ < n)
	{
		if (*str2 == (unsigned char)c)
			return ((void *)str2);
		str2++;
	}
	return ((void *)0);
}
