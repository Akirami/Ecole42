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
	mouse_events(int btn, int x, int y, t_stuff *stuff)
{
	if (x > 6 && x < 16 && y > -16 && y < -6)
		close_minirt(stuff);
	(void)btn;
	(void)x;
	(void)y;
	(void)stuff;
	return (0);
}

int
	no_events(int ev, t_stuff *st)
{
	(void)st;
	(void)ev;
	return (0);
}

int
	init_obj(t_stuff *st)
{
	int n;

	n = 0;
	while (n < st->li_count)
	{
		st->lights[n] = st->obj.lights[n];
		n++;
	}
	n = 0;
	while (n < st->cam_count)
	{
		st->cam[n] = st->obj.cam[n];
		n++;
	}
	mlx_key_hook(st->window.win, key_events, st);
	mlx_mouse_hook(st->window.win, mouse_events, st);
	mlx_hook(st->window.win, 17, 0, hook_events, st);
	st->filt.col[0] = 1;
	st->filt.col[1] = 1;
	st->filt.col[2] = 1;
	st->filt.bw = 0;
	st->filt.sepia = 0;
	return (1);
}

int
	mem_texture(t_stuff *st)
{
	int		i;
	int		img_size;

	i = -1;
	if (!(st->img = (char **)malloc(st->cam_count * sizeof(char *))))
			return (0);
	img_size = st->window.width * st->window.height * 4;
	while (++i < st->cam_count)
	{
		if (!(st->img[i] = (char *)malloc(img_size * sizeof(char))))
			return (0);
	}
	return (1);
}

int
	main_loop(t_stuff *st)
{
	int		i;
	int		res;

	i = -1;
	res = 1;
	init_obj(st);
	res *= load_textures(st);
	if (!res)
		error_message("Issu occured while loading textures.", st);
	st->im.ptr = mlx_new_image(st->context,
		st->window.width, st->window.height);
	st->im.data = mlx_get_data_addr(st->im.ptr,
		&st->im.bpp, &st->im.sizeline, &st->im.endian);
	if (!mem_texture(st))
		return (0);
	st->icam = 0;
	st->cam[st->icam] = st->obj.cam[st->icam];
	res *= prepare_stuff(st);
	if (!res)
		return (0);
	if (!st->save)
		mlx_loop(st->context);
	return (1);
}
