/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 17:46:50 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 23:42:43 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void
	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	const char		*src2;

	i = 0;
	dst2 = (unsigned char *)dst;
	src2 = (const char *)src;
	if (len != 0 && src == NULL && dst == NULL)
		return ((void *)0);
	while (i < len)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}
