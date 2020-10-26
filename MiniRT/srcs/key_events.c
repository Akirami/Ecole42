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
	change_cam(t_stuff *st, int key)
{
	if (key == 116)
	{
		st->icam--;
		if (st->icam < 0)
			st->icam = 0;
		prepare_stuff(st);
	}
	else if (key == 121)
	{
		st->icam++;
		if (st->icam >= st->cam_count)
			st->icam = 0;
		prepare_stuff(st);
	}
}

void
	apply_filters(t_stuff *st, double key)
{
	if (key == 18)
		set_filters(st, 1, 1, 1);
	else if (key == 19)
		set_filters(st, 1, 0, 0);
	else if (key == 20)
		set_filters(st, 0, 1, 0);
	else if (key == 21)
		set_filters(st, 0, 0, 1);
	else if (key == 23)
	{
		set_filters(st, 1, 1, 1);
		st->filt.sepia = 0;
		st->filt.bw = !st->filt.bw;
	}
	else if (key == 22)
	{
		set_filters(st, 1, 1, 1);
		st->filt.bw = 0;
		st->filt.sepia = !st->filt.sepia;
	}
	st->cam[st->icam].isdraw = 0;
	prepare_stuff(st);
}

void
	move_cam(t_stuff *st, double *xy, double x)
{
	*xy += x;
	st->cam[st->icam].isdraw = 0;
	prepare_stuff(st);
}

void
	rotate(t_stuff *st, int key)
{
	vec		v;
	vec		rdir;

	printf("YOLO\n");
	v = vectorsub(st->cam[st->icam].look_at, st->cam[st->icam].pos);
	if (key == 123)
		ry(&st->cam[st->icam].look_at, M_PI / 8);
	else if (key == 124)
		ry(&st->cam[st->icam].look_at, M_PI / -8);
	else if (key == 125)
	{
		rx(&st->cam[st->icam].look_at, M_PI / -8);
	}
	else if (key == 126)
	{
		rx(&st->cam[st->icam].look_at, M_PI / 8);
	}
	rdir = vectorsub(st->cam[st->icam].look_at, st->cam[st->icam].pos);
	normalize_v(rdir);
	st->cam[st->icam].isdraw = 0;
	prepare_stuff(st);
}

int
	key_events(int key, t_stuff *st)
{
	printf("KEYCODE: %d\n", key);
	if (key == 49)
		display_hud(st);
	else if (key == 116)
		change_cam(st, key);
	else if (key == 121)
		change_cam(st, key);
	else if (key == 53)
		close_minirt(st);
	else if (key >= 18 && key <= 23)
		apply_filters(st, key);
	else if (key == 2)
		move_cam(st, &st->cam[st->icam].pos.x, 50);
	else if (key == 0)
		move_cam(st, &st->cam[st->icam].pos.x, -50);
	else if (key == 1)
		move_cam(st, &st->cam[st->icam].pos.y, -50);
	else if (key == 13)
		move_cam(st, &st->cam[st->icam].pos.y, 50);
	else if (key >= 123 && key <= 126)
		rotate(st, key);
	return (0);
}
