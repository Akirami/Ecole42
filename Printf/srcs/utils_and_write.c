/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_base.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/07 17:53:02 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/09 10:09:52 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void
	ft_putnbr_custom(int n, t_flags *flags, t_count *counter)
{
	int64_t	j;
	char	c;

	j = (int64_t)n;
	if (j == -2147483648 && flags->is_neg_p)
		j = (long int)2147483648;
	if (j < 0)
	{
		flags->p_len2++;
		ft_putchar_count('-', counter);
		j *= -1;
	}
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

int
	size_int(int64_t n)
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
	ft_putchar_count(char c, t_count *counter)
{
	write(1, &c, 1);
	counter->count++;
}

void
	ft_putstr_or_null(char *s, t_count *counter)
{
	int i;

	i = 0;
	if (s == NULL)
	{
		s = ft_strdup("(null)");
		while (s[i])
		{
			ft_putchar_count(s[i], counter);
			i++;
		}
		free(s);
		return ;
	}
	while (*s)
	{
		ft_putchar_count(*s, counter);
		s++;
	}
}

int
	my_test_star(t_flags *flags, int star_value)
{
	if (star_value < 0 && !flags->point)
	{
		flags->minus = 1;
		star_value *= -1;
	}
	if (star_value < 0 && flags->point && flags->star)
	{
		flags->prec_zero_unsigned = 0;
		flags->prec_zero = 0;
	}
	if (star_value == 0 && flags->point)
	{
		flags->prec_zero_unsigned = 1;
		flags->prec_zero = 1;
	}
	return (star_value);
}
