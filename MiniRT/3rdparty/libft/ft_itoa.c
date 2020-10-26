/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:54:56 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:54:56 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int
	ft_slen(long int x, int j)
{
	if (x > 9 || x < -9)
	{
		j = ft_slen(x / 10, ++j);
	}
	return (j);
}

static char
	ft_nbrtostr(int n)
{
	if (n < 0)
		n *= -1;
	return (n + 48);
}

static char
	*ft_revstr(char *str)
{
	char	tmp;
	char	*save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	save = str;
	if (*str == '-')
		str++;
	while (str[i])
		i++;
	while (i > j)
	{
		tmp = str[j];
		str[j] = str[i - 1];
		str[i - 1] = tmp;
		i--;
		j++;
	}
	return (save);
}

char
	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_slen((long int)n, 1);
	if (n < 0)
		len++;
	if (!(str = (char *)malloc((len + 1) * sizeof(char))))
		return ((char *)0);
	if (n < 0)
	{
		str[i] = '-';
		i = 1;
	}
	while (i < len)
	{
		str[i] = ft_nbrtostr(n % 10);
		n = n / 10;
		i++;
	}
	str[i] = '\0';
	return (ft_revstr(str));
}
