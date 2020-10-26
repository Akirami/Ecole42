/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/18 14:07:31 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 17:03:36 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

int
	ft_slen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	return (i);
}

int
	check_return(int res, char *str, char **line)
{
	if (res < 0)
		return (-1);
	if (res == 0 && !str[0])
	{
		*line = str;
		return (0);
	}
	return (1);
}

int
	get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*s[4401];
	char		*tmp;
	int			res;
	int			i;

	if ((i = 0) || fd < 0 || fd > 4400 || line == NULL)
		return (-1);
	(s[fd] == NULL) ? s[fd] = ft_strnew(0) : s[fd];
	while (!(ft_strchr(s[fd], '\n')) && (res = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[res] = '\0';
		tmp = s[fd];
		s[fd] = ft_strjoin(tmp, buff);
		free(tmp);
	}
	i = ft_slen(s[fd]);
	if (check_return(res, s[fd], line) < 1)
		return (check_return(res, s[fd], line));
	*line = ft_strsub(s[fd], 0, i);
	tmp = s[fd];
	s[fd] = ft_strdup(tmp + i + (tmp[i] != 0));
	free(tmp);
	return (1);
}
