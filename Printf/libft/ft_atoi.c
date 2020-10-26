/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/07 17:13:40 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 15:35:34 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

int
	ft_atoi(const char *str)
{
	int		nb;
	int		sign;

	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r')
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
