/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/07 13:40:14 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 20:18:52 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

size_t
	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	n;
	size_t	l;
	size_t	tot;

	n = 0;
	l = 0;
	tot = 0;
	while ((j = 0) || src[n] != '\0')
		n++;
	while (dest[l] != '\0')
		l++;
	if (l > size)
		return (n + size);
	tot = (l + n);
	while (src[j] && l < size - 1)
	{
		dest[l] = src[j];
		j++;
		l++;
	}
	dest[l] = '\0';
	if (size == 0)
		return (n);
	return (tot);
}
