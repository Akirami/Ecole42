/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:10 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:10 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char
	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(needle);
	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (i < len && *haystack)
	{
		if ((j + i) > len)
			return (NULL);
		if ((*haystack == *needle) && !ft_memcmp(haystack, needle, j))
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return ((char *)0);
}
