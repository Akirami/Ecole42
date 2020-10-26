/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:10 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:10 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int
	ft_slen(const char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char
	*ft_strmap(char const *s, char (*f)(char))
{
	char			*s2;
	unsigned int	i;

	i = 0;
	if (!(s2 = (char*)malloc((ft_slen(s) + 1) * sizeof(char))))
		return (NULL);
	while (*s)
	{
		s2[i] = (char)f(*s);
		s++;
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
