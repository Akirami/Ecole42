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

void
	set_filters(t_stuff *st, int a, int b, int c)
{
	st->filt.bw = 0;
	st->filt.sepia = 0;
	st->filt.col[0] = a;
	st->filt.col[1] = b;
	st->filt.col[2] = c;
}

void
	display_hud(t_stuff *st)
{
	if (st->is_hud)
	{
		mlx_clear_window(st->context, st->window.win);
		mlx_put_image_to_window(st->context, st->window.win, st->im.ptr, 0, 0);
		st->is_hud = false;
	}
	else
	{
		st->is_hud = true;
		draw_hud(st);
	}
}

bool
	check_c_range_uint(char c)
{
	if (c >= 48 && c <= 57)
		return (true);
	return (false);
}

int
	prepare_stuff(t_stuff *st)
{
	int		img_size;
	int		res;
	clock_t	end;

	res = 1;
	st->window.scale = tan(st->cam[st->icam].fov * 0.5);
	st->window.ratio = st->window.width / (double)st->window.height;
	img_size = st->window.width * st->window.height * 4;
	if (!st->cam[st->icam].isdraw)
	{
		res *= draw_scene(st);
		st->img[st->icam] = ft_memcpy(st->img[st->icam], st->im.data, img_size);
		st->cam[st->icam].isdraw = 1;
	}
	else
		st->im.data = ft_memcpy(st->im.data, st->img[st->icam], img_size);
	(!st->save) ? mlx_put_image_to_window(st->context,
		st->window.win, st->im.ptr, 0, 0) : save_img(st);
	end = clock();
	st->millis = (end - st->t_begin) * 1000 / CLOCKS_PER_SEC;
	if (st->is_hud)
		draw_hud(st);
	return (res);
}
