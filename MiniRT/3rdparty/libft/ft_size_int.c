/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:05 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:05 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int
	ft_size_int(int64_t n)
{
	int i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	if (n > 0)
		i++;
	return (i);
}