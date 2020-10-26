/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 11:43:02 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 11:43:18 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

int
	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;
	char	*str3;
	char	*str4;

	str3 = (char *)str1;
	str4 = (char *)str2;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)*str3 != (unsigned char)*str4)
			return ((unsigned char)*str3 - (unsigned char)*str4);
		i++;
		str3++;
		str4++;
	}
	return (0);
}
