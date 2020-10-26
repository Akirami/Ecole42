/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:04 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:04 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void
	ft_putnbr_fd(int n, int fd)
{
	long long int	j;
	char			c;

	j = (long long int)n;
	if (j < 0)
	{
		write(fd, "-", 1);
		j *= -1;
	}
	if (j > 9)
	{
		ft_putnbr_fd(j / 10, fd);
		ft_putnbr_fd(j % 10, fd);
	}
	else
	{
		c = j + 48;
		write(fd, &c, 1);
	}
}
