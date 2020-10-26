/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 11:49:44 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 17:59:05 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
