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

#include "../../includes/minirt.h"

int
	set_color(double color[3])
{
	int rgb[4];

	rgb[0] = 0;
	rgb[1] = (unsigned int)min(color[0] * 255, 255);
	rgb[2] = (unsigned int)min(color[1] * 255, 255);
	rgb[3] = (unsigned int)min(color[2] * 255, 255);
	return (rgb_to_hex(rgb));
}

void
	compute_camera(t_stuff *st, vec *translation)
{
	vec up;
	vec eye;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	eye = vectorsub(st->cam[st->icam].look_at, st->cam[st->icam].pos);
	if (eye.x == 0 && eye.z == 0)
	{
		eye.x = 0;
		eye.y = 0.9999;
		eye.z = 0.0001;
	}
	st->cam[st->icam].eye = st->cam[st->icam].look_at;
	normalize_vec(&st->cam[st->icam].eye);
	st->cam[st->icam].right = vectorcross(st->cam[st->icam].eye, up);
	normalize_vec(&st->cam[st->icam].right);
	st->cam[st->icam].up = vectorcross(st->cam[st->icam].right,
		st->cam[st->icam].eye);
	normalize_vec(&st->cam[st->icam].up);
	translation->x = -vectordot(st->cam[st->icam].pos, st->cam[st->icam].right);
	translation->y = -vectordot(st->cam[st->icam].pos, st->cam[st->icam].up);
	translation->z = -vectordot(st->cam[st->icam].pos, st->cam[st->icam].eye);
}

void
	init_var(t_stuff *st, t_var *tv, double x, double y)
{
	vec transl;
	vec dir;
	vec src[3];
	vec image_point;

	tv->level = 0;
	tv->coef = 0.6;
	tv->r.start = st->cam[st->icam].pos;
	tv->r.start.x = (2 * (x / (double)st->window.width) - 1)
		* st->window.scale * st->window.ratio;
	tv->r.start.y = (1 - 2 * y / (double)st->window.height) * st->window.scale;
	compute_camera(st, &transl);
	src[0] = vectorscale(tv->r.start.x, st->cam[st->icam].right);
	src[1] = vectorscale(tv->r.start.y, st->cam[st->icam].up);
	src[2] = vectoradd(st->cam[st->icam].pos, st->cam[st->icam].eye);
	image_point = vectoradd3(src[0], src[1], src[2]);
	dir = vectorsub(image_point, st->cam[st->icam].pos);
	normalize_vec(&dir);
	tv->r.dir = dir;
	tv->r.start.x += st->cam[st->icam].pos.x;
	tv->r.start.y += st->cam[st->icam].pos.y;
	tv->rgb[0] = st->amb.color.r;
	tv->rgb[1] = st->amb.color.g;
	tv->rgb[2] = st->amb.color.b;
}

t_inter
	find_object(t_stuff *st, ray *r)
{
	t_inter closest;
	t_inter	ti;
	int		i;

	ft_bzero(&closest, sizeof(t_inter));
	closest.t = 20000000;
	ti.t = 20000000;
	ti.is_l = false;
	ti.opos = r->start;
	ti.odir = r->dir;
	i = -1;
	while (++i < st->obj_count)
	{
		ti = g_func_ptr[st->objs[i].type](st, st->objs[i].ptr, &ti, r);
		if (ti.t < closest.t && ti.match)
			closest = ti;
	}
	return (closest);
}
