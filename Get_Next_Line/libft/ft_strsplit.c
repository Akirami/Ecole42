/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 16:34:10 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 15:56:55 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

static char
	*ft_strdup_m(const char *src, char c, int i)
{
	char	*str;
	char	*str3;

	while (src[i] && src[i] == c)
		src++;
	while (src[i] && src[i] != c)
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	str3 = str;
	while (*src && *src != c)
		*str++ = *src++;
	*str = '\0';
	return (str3);
}

static char
	**ft_get_word(char **strs, const char *str, char c)
{
	const char	*str2;
	int			i;

	i = 0;
	str2 = str;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		while (*str && *str != c)
		{
			while (*str && *str != c)
				str++;
			strs[i] = ft_strdup_m(str2, c, 0);
			str2 = str;
			i++;
		}
	}
	return (strs);
}

char
	**ft_strsplit(char const *s, char c)
{
	int			k;
	char		**strs;
	const char	*str2;

	str2 = s;
	k = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		while (*s && *s != c)
		{
			while (*s && *s != c)
				s++;
			k++;
		}
	}
	if (!(strs = (char**)malloc((k + 1) * sizeof(char*))))
		return ((char **)0);
	strs[k] = 0;
	if (c == 0)
		strs[0] = ft_strdup_m(s, c, 0);
	else
		strs = ft_get_word(strs, str2, c);
	return (strs);
}
