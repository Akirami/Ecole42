/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:05 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:05 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char
	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (*s == '\0')
			return ((char *)0);
		s++;
	}
	return ((char *)s);
}