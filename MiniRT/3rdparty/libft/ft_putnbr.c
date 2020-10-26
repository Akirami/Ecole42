/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:03 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:03 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void
	ft_putnbr(int n)
{
	long long int	j;
	char			c;

	j = (long long int)n;
	if (j < 0)
	{
		write(1, "-", 1);
		j *= -1;
	}
	if (j > 9)
	{
		ft_putnbr(j / 10);
		ft_putnbr(j % 10);
	}
	else
	{
		c = j + 48;
		write(1, &c, 1);
	}
}
