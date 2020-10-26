/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:07 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:07 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char
	*ft_strdup(const char *src)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	while (src[i])
		i++;
	if (!(str = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	str2 = str;
	while (*src)
		*str++ = *src++;
	*str = '\0';
	return (str2);
}
