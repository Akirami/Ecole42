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

int
	get_xpm(t_stuff *st, char **filename)
{
	int i;

	i = -1;
	while (++i < TEXTURES)
	{
		st->text[i].ptr = mlx_xpm_file_to_image(st->context, filename[i],
			&st->text[i].width, &st->text[i].height);
		ft_putstr(filename[i]);
		ft_putstr("\n");
		ft_putnbr(st->text[i].width);
		ft_putstr(" x ");
		ft_putnbr(st->text[i].height);
		ft_putstr("\n");
		if (st->text[i].ptr == NULL)
			return (0);
		st->text[i].data = mlx_get_data_addr(st->text[i].ptr,
			&st->text[i].bpp, &st->text[i].sizeline, &st->text[i].endian);
	}
	return (1);
}

int
	load_textures(t_stuff *st)
{
	char	*filename[TEXTURES + 1];

	filename[0] = "./images/earth.xpm";
	filename[1] = "./images/eye.xpm";
	filename[2] = "./images/nice.xpm";
	filename[3] = "./images/night.xpm";
	filename[4] = "./images/soleil.xpm";
	filename[5] = "./images/water.xpm";
	filename[6] = "./images/water2.xpm";
	filename[7] = "./images/moon/back.xpm";
	filename[8] = "./images/moon/bottom.xpm";
	filename[9] = "./images/moon/front.xpm";
	filename[10] = "./images/moon/left.xpm";
	filename[11] = "./images/moon/right.xpm";
	filename[12] = "./images/moon/top.xpm";
	return (get_xpm(st, filename));
}
