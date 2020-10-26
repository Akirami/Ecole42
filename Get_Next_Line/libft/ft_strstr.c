/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/05 17:27:11 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 20:11:31 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

static int
	ft_slen(const char *str)
{
	int i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}

static int
	ft_cmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

char
	*ft_strstr(const char *haystack, const char *needle)
{
	if (*needle == 0)
		return ((char *)haystack);
	if (ft_slen(needle) > ft_slen(haystack))
		return ((char *)0);
	while (*haystack != '\0')
	{
		if ((*haystack == *needle) && ft_cmp(haystack, needle))
			return ((char *)haystack);
		haystack++;
	}
	return ((char *)0);
}
