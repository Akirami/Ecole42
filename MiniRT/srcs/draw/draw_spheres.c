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

color
	chess_map_sp(vec pt, color col, double type, t_sp sp)
{
	color	invcol;
	double	theta;
	double	phi;
	double	d[2];
	vec		new;

	invcol.r = 1 - col.r;
	invcol.g = 1 - col.g;
	invcol.b = 1 - col.b;
	if (type == 1)
	{
		new = vectorsub(pt, sp.pos);
		theta = atan2(new.x, new.z) / (2 * M_PI);
		phi = acos(new.y / sp.radius);
		d[0] = (1 - (theta + 0.5)) * 2 * (sp.radius / 5);
		d[1] = (phi / M_PI) * (sp.radius / 5);
		if (((int)d[0] + (int)d[1]) % 2 == 0)
			return (invcol);
		return (col);
	}
	return (col);
}

void
	getpixel(t_stuff *st, double u, double v, t_inter *ti)
{
	unsigned int	x;
	unsigned int	y;
	double			rgb[3];
	int				id;

	id = ti->mat.type;
	x = (int)(u * st->text[id].width);
	y = (int)(v * st->text[id].height);
	x = (unsigned int)min(x, st->text[id].width);
	y = (unsigned int)min(y, st->text[id].height);
	id = *(int *)(st->text[id].data + (x * 4 + (y * st->text[id].sizeline)));
	rgb[0] = (id >> 16) & 0xFF;
	rgb[1] = (id >> 8) & 0xFF;
	rgb[2] = (id) & 0xFF;
	ti->mat.diffuse.r = (double)(rgb[0] / 255);
	ti->mat.diffuse.g = (double)(rgb[1] / 255);
	ti->mat.diffuse.b = (double)(rgb[2] / 255);
}

void
	sp_map(t_stuff *st, t_inter *ti, t_sp *sp)
{
	vec		polequator[2];
	vec		normal;
	double	theta;
	double	u;
	double	v;

	if (sp->mat.type == 1)
	{
		ti->mat.diffuse = chess_map_sp(ti->hit, ti->mat.diffuse, 1, *sp);
		return ;
	}
	n_vec(0, 1, 0, &polequator[0]);
	n_vec(1, 0, 0, &polequator[1]);
	normal = vectorsub(ti->hit, sp->pos);
	normalize_vec(&normal);
	v = acos(-vectordot(polequator[0], normal)) / M_PI;
	theta = (acos(vectordot(normal, polequator[1]) /
		sin(acos(-vectordot(polequator[0], normal))))) / (2 * M_PI);
	if (vectordot(vectorcross(polequator[0], polequator[1]), normal) > 0)
		u = theta;
	else
		u = 1 - theta;
	v = 1 - v;
	ti->mat.type -= 10;
	getpixel(st, u, v, ti);
}

t_inter
	calc_sp_ti(t_stuff *st, t_inter *ti, t_sp sp, ray *r)
{
	ti->hit = vectoradd(r->start, vectorscale(ti->t, r->dir));
	ti->n = vectorsub(ti->hit, sp.pos);
	if (vectordot(ti->n, ti->n) == 0)
		return (invalid_ti(ti));
	normalize_vec(&ti->n);
	ti->mat = sp.mat;
	if (sp.mat.type != 0)
		sp_map(st, ti, &sp);
	return (*ti);
}

t_inter
	intersect_r_sp(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_sp			sp;
	t_r_inter_sp	tz;
	vec				dist;

	sp = *(t_sp *)ptr;
	ti->match = true;
	dist = vectorsub(r->start, sp.pos);
	tz.a = vectordot(r->dir, r->dir);
	tz.b = 2 * vectordot(r->dir, dist);
	tz.c = vectordot(dist, dist) - (sp.radius * sp.radius);
	tz.discr = tz.b * tz.b - 4 * tz.a * tz.c;
	if (tz.discr < EPSILON)
		return (invalid_ti(ti));
	tz.sqrtdiscr = sqrt(tz.discr);
	tz.t0 = (-tz.b + tz.sqrtdiscr) / (2);
	tz.t1 = (-tz.b - tz.sqrtdiscr) / (2);
	if (tz.t0 > tz.t1)
		tz.t0 = tz.t1;
	if ((tz.t0 > EPSILON))
		ti->t = tz.t0;
	else
		return (invalid_ti(ti));
	return (calc_sp_ti(st, ti, sp, r));
}
