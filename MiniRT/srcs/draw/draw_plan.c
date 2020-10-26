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
	get_disrupt(t_inter *ti, t_sq *sq)
{
	color	invcol;
	color	col;
	vec		ap;
	double	sines;

	col = sq->mat.diffuse;
	invcol.r = 1 - col.r;
	invcol.g = 1 - col.g;
	invcol.b = 1 - col.b;
	ap = vectorsub(ti->hit, sq->pos);
	normalize_vec(&ap);
	if (sq->mat.type == 1)
	{
		sines =
			sin((1 / (2 * M_PI)) * ((ti->hit.x != 0) ? ti->hit.x : 1)) *
			sin((1 / (2 * M_PI)) * ((ti->hit.y != 0) ? ti->hit.y : 1)) *
			sin((1 / (2 * M_PI)) * ((ti->hit.z != 0) ? ti->hit.z : 1));
		if (sines < 0)
			return (col);
		else
			return (invcol);
	}
	return (col);
}

color
	chess_map_sqpl(vec p, color col, vec pos, vec norm)
{
	t_rep	rep;
	double	d[2];
	double	size;
	int		check;
	color	invcol;

	invcol.r = 1 - col.r;
	invcol.g = 1 - col.g;
	invcol.b = 1 - col.b;
	size = 1.0 / 50;
	rep = calc_rep(norm);
	rep.v = vectorscale(size, rep.v);
	rep.w = vectorscale(size, rep.w);
	d[0] = vectordot(vectorsub(p, pos), rep.v);
	d[1] = vectordot(vectorsub(p, pos), rep.w);
	check = ((fabs(fmod(d[0], 2)) > 0.5 && fabs(fmod(d[0], 2)) < 1.5) ? 1 : -1);
	if (fabs(fmod(d[1], 2)) > 0.5 && fabs(fmod(d[1], 2)) < 1.5)
		check = -check;
	if (check == 1)
	{
		return (col);
	}
	return (invcol);
}

vec
	valid_obj(t_inter *ti)
{
	double	t[4];

	t[0] = calc_dist(ti->opos, ti->hit);
	t[1] = calc_dist(ti->opos, vectoradd(ti->hit, ti->n));
	t[2] = calc_dist(ti->lpos, ti->hit);
	t[3] = calc_dist(ti->lpos, vectoradd(ti->hit, ti->n));
	if (!ti->is_l)
	{
		if (t[3] < t[2])
		{
			if (t[1] < t[0])
				return (normalize_v(ti->n));
			else
				return (normalize_v(vectorscale(-1, ti->n)));
		}
		else
		{
			if (t[1] > t[0])
				return (normalize_v(vectorscale(-1, ti->n)));
			else
				return (normalize_v(ti->n));
		}
	}
	return (ti->n);
}

t_inter
	intersect_r_sq(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_sq	sq;
	double	dist;

	sq = *(t_sq *)ptr;
	ti->match = true;
	dist = vectordot(vectorsub(sq.pos, r->start),
		sq.norm) / vectordot(r->dir, sq.norm);
	if (dist < EPSILON)
		return (invalid_ti(ti));
	ti->hit = vectoradd(r->start, vectorscale(dist, r->dir));
	if (!(fabs(vectordot(vectorsub(ti->hit, sq.pos),
		sq.sqp.e1)) < pow(sq.len / 2, 2) &&
			fabs(vectordot(vectorsub(ti->hit, sq.pos),
				sq.sqp.e2)) < pow(sq.len / 2, 2)))
		return (invalid_ti(ti));
	ti->n = sq.norm;
	ti->t = dist;
	ti->n = valid_obj(ti);
	ti->mat = sq.mat;
	if (sq.mat.type != 0)
		mapping_sq(st, ti, &sq);
	return (*ti);
}

t_inter
	intersect_r_pl(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_pl	pl;
	double	dist;
	double	den;
	double	b;

	pl = *(t_pl *)ptr;
	ti->match = true;
	(void)st;
	normalize_vec(&pl.norm);
	den = -vectordot(pl.pos, pl.norm);
	b = vectordot(r->dir, pl.norm);
	(b == 0) ? b = EPSILON : b;
	dist = -((vectordot(pl.norm, r->start) + den) / b);
	if (dist < EPSILON || dist > ti->t)
		return (invalid_ti(ti));
	ti->t = dist;
	ti->hit = vectoradd(r->start, vectorscale(dist, r->dir));
	ti->n = pl.norm;
	ti->n = valid_obj(ti);
	ti->mat = pl.mat;
	if (pl.mat.type != 0)
		ti->mat.diffuse = chess_map_sqpl(ti->hit, ti->mat.diffuse,
			pl.pos, pl.norm);
	return (*ti);
}
