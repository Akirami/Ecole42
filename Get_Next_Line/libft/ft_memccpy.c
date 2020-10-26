/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 22:02:35 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 01:05:21 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void
	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	i = 0;
	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (len != 0 && src == NULL && dst == NULL)
		return ((void *)0);
	while (i < len)
	{
		dst2[i] = (unsigned char)src2[i];
		if (src2[i] == (unsigned char)c)
			return (dst2 + i + 1);
		i++;
	}
	if ((i > 0) && (src2[i - 1] == c))
		return (dst2 + i);
	return (0);
}
