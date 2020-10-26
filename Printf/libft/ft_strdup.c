/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/11 10:11:21 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 20:50:15 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char
	*ft_strdup(const char *src)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	while (src[i])
		i++;
	if (!(str = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	str2 = str;
	while (*src)
		*str++ = *src++;
	*str = '\0';
	return (str2);
}
