/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 11:50:20 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 17:59:16 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
