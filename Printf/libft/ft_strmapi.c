/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 11:47:57 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 03:23:10 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

static int
	ft_slen(const char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char
	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s2;
	unsigned int	i;

	i = 0;
	if (!(s2 = (char*)malloc((ft_slen(s) + 1) * sizeof(*s))))
		return (NULL);
	while (*s)
	{
		s2[i] = (char)f(i, *s);
		s++;
		i++;
	}
	s2[i] = '\0';
	return (s2);
}