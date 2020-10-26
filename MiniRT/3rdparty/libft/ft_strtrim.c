/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:12 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:12 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char
	*ft_ssub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!(str = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (*s && (i < len))
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char
	*ft_strtrim(char const *str)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
		i++;
	while (str[j] == ' ' || str[j] == '\n' || str[j] == '\t')
		j++;
	while (j < i && (str[i - 1] == ' ' || str[i - 1] == '\n'
				|| str[i - 1] == '\t'))
		i--;
	if ((i - j) <= 0)
		return ("");
	if (i == j)
		return ((char *)str);
	return (ft_ssub(str, j, (i - j)));
}
