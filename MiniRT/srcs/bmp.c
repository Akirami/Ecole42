/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bonus_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 07:04:24 by emassard          #+#    #+#             */
/*   Updated: 2020/03/02 07:04:27 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char
	*create_file_name(t_stuff *st)
{
	char	*tmp[4];

	st->filename = ft_strdup("img");
	tmp[0] = ft_strrchr(st->filename, '/');
	if (!tmp[0])
		tmp[0] = st->filename;
	else
		tmp[0]++;
	tmp[1] = ft_strjoin(SAVE_DIR, tmp[0]);
	if (st->cam_count > 1)
	{
		tmp[2] = ft_itoa(st->icam);
		tmp[3] = ft_strjoin("_cam_", tmp[2]);
		free(tmp[2]);
		tmp[0] = ft_strjoin(tmp[3], ".bmp");
		free(tmp[3]);
		tmp[3] = ft_strjoin(tmp[1], tmp[0]);
		free(tmp[0]);
		tmp[0] = tmp[3];
	}
	else
		tmp[0] = ft_strjoin(tmp[1], ".bmp");
	free(tmp[1]);
	return (tmp[0]);
}

void
	bmp_header(t_stuff *st, char **data)
{
	unsigned int	size;

	size = (unsigned int)(st->window.width * st->window.height * 3);
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + 122);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = 122;
	*(unsigned int *)(*data + 14) = 122 - 14;
	*(unsigned int *)(*data + 18) = st->window.width;
	*(unsigned int *)(*data + 22) = st->window.height;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

void
	fill_img(t_stuff *st, char **buffer)
{
	int			it[3];
	color		pixel;

	it[0] = st->window.height;
	it[2] = 122;
	while (--it[0] >= 0)
	{
		it[1] = -1;
		while (++it[1] < st->window.width)
		{
			pixel = h_to_rgb(*(int*)(st->im.data
					+ (it[1] * 4 + (it[0] * st->im.sizeline))));
			*(*buffer + it[2]++) = (char)pixel.b;
			*(*buffer + it[2]++) = (char)pixel.g;
			*(*buffer + it[2]++) = (char)pixel.r;
		}
	}
}

int
	build_img(t_stuff *st)
{
	char		*buffer;
	int			size;
	int			fd;

	size = st->window.width * st->window.height * 3;
	if (!(buffer = (char *)malloc(size + 122)))
		return (0);
	st->filename = create_file_name(st);
	bmp_header(st, &buffer);
	fill_img(st, &buffer);
	if ((fd = open(st->filename, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		return (0);
	write(fd, buffer, (size + 122));
	free(buffer);
	close(fd);
	return (1);
}

int
	save_img(t_stuff *st)
{
	int		i;
	int		res;

	res = 1;
	i = -1;
	while (++i < st->cam_count)
	{
		res *= build_img(st);
		if (st->icam == st->cam_count - 1)
			break ;
		st->icam++;
		if (st->icam < st->cam_count)
			prepare_stuff(st);
	}
	return (res);
}
