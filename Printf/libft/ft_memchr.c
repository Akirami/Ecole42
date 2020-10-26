/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 11:42:18 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 15:34:10 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void
	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*str2;

	str2 = (unsigned char *)str;
	i = 0;
	while (i++ < n)
	{
		if (*str2 == (unsigned char)c)
			return ((void *)str2);
		str2++;
	}
	return ((void *)0);
}
