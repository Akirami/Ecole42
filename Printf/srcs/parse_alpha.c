/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_alpha.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 08:35:10 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 08:35:22 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char
	*ft_hexa(uint64_t nbr, char *base, uint64_t i)
{
	char	*hexa;
	char	*tmp;
	char	*tmp2;

	hexa = ft_strnew(0);
	while (nbr >= i)
	{
		tmp = hexa;
		tmp2 = char_convert(base[nbr % i]);
		hexa = ft_strjoin(hexa, tmp2);
		free(tmp);
		free(tmp2);
		nbr = nbr / i;
	}
	return (hexa);
}

int
	size_alpha(int64_t n)
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
