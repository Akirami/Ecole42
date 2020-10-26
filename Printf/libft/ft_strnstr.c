/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/05 17:27:11 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 15:36:33 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char
	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(needle);
	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (i < len && *haystack)
	{
		if ((j + i) > len)
			return (NULL);
		if ((*haystack == *needle) && !ft_memcmp(haystack, needle, j))
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return ((char *)0);
}
