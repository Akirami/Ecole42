/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:54:34 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:54:37 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int
	ft_atoi(const char *str)
{
	int		nb;
	int		sign;

	sign = 1;
	while (ft_strchr("\t\v\n\f\r ", *str))
		str++;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if ((nb = 0) || *str == '-' || *str == '+')
		return (0);
	while (*str >= 48 && *str <= 57)
	{
		if (nb < 0 && sign == 1)
			return (-1);
		if (nb < 0 && sign == -1)
			return (0);
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}
