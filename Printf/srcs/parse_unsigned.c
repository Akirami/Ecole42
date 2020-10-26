/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_unsigned.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 08:20:04 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 08:21:51 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int
	size_unsigned(int64_t n)
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
	return (i);
}

void
	ft_putnbr_unsigned(uint64_t n, t_flags *flags, t_count *counter)
{
	uint64_t	j;
	char		c;

	j = n;
	if (j > 9)
	{
		ft_putnbr_custom(j / 10, flags, counter);
		ft_putnbr_custom(j % 10, flags, counter);
	}
	else
	{
		c = j + 48;
		ft_putchar_count(c, counter);
	}
}

void
	ft_base_convert(uint64_t nbr, char *base, uint64_t i, t_count *counter)
{
	if (nbr >= i)
	{
		ft_base_convert(nbr / i, base, i, counter);
		ft_putchar_count(base[nbr % i], counter);
	}
	if (nbr < i)
		ft_putchar_count(base[nbr], counter);
}

void
	ft_base_p_convert(uint64_t nbr, char *base, uint64_t i, t_count *counter)
{
	ft_putstr_or_null("0x", counter);
	ft_base_convert(nbr, base, i, counter);
}

void
	ft_putnbr_base(int64_t nbr, char *base, t_count *counter)
{
	int64_t i;

	ft_putstr_or_null("0x", counter);
	i = 0;
	while (base[i] != '\0')
		i++;
	ft_base_convert(nbr, base, i, counter);
}
