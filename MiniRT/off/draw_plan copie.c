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

void
	prepare_sq_map(t_sq *sq)
{
	vec v2;
	vec v3;
	vec v4;

	sq->sqp.v1 = vectoradd(vectoradd(sq->pos, sq->sqp.e1), vectorscale(-1, sq->sqp.e2));
	v2 = vectoradd(vectoradd(sq->pos, sq->sqp.e1), sq->sqp.e2);
	v3 = vectoradd(vectoradd(sq->pos, vectorscale(-1, sq->sqp.e1)), vectorscale(-1, sq->sqp.e2));
	v4 = vectoradd(vectoradd(sq->pos, vectorscale(-1, sq->sqp.e1)), sq->sqp.e2);
	sq->sqp.z2 = vectorsub(sq->sqp.v1, v2);
	sq->sqp.z3 = vectorsub(sq->sqp.v1, v3);
	sq->sqp.d2 = vectordot(sq->sqp.z2, sq->sqp.z2);
	sq->sqp.d3 = vectordot(sq->sqp.z3, sq->sqp.z3);
}


void
	prepare_sq(t_sq *sq)
{
	vec		u;
	vec		v;
	vec		w;

	u = sq->norm;
	normalize_vec(&u);
	v.x = 0;
	v.y = 1;
	v.z = 0;
	if (u.x == 0 && u.z == 0)
	{
		v.y = 0.9999;
		v.z = 0.0001;
	}
	normalize_vec(&v);
	v = vectorsub(v, vectorscale(vectordot(u, v), u));
	normalize_vec(&v);
	w = vectorcross(v, u);
	normalize_vec(&w);
	sq->sqp.e1 = vectorsub(vectoradd(sq->pos, vectorscale(sq->len / 2, v)), sq->pos);
	sq->sqp.e2 = vectorsub(vectoradd(sq->pos, vectorscale(sq->len / 2, w)), sq->pos);
	sq->sqp.de1 = vectordot(sq->sqp.e1, sq->sqp.e1);
	sq->sqp.de2 = vectordot(sq->sqp.e2, sq->sqp.e2);
	printf("SQMAT: %f %f %f \n", sq->mat.diffuse.r, sq->mat.diffuse.g, sq->mat.diffuse.b);
	printf("SQPOS: %f %f %f \n", sq->pos.x, sq->pos.y, sq->pos.z);
	prepare_sq_map(sq);
}

color
	get_disrupt(t_inter *ti, t_sq *sq)
{
	color	invcol;
	color	col;

	col = sq->mat.diffuse;
	invcol.r = 1 - col.r;
	invcol.g = 1 - col.g;
	invcol.b = 1 - col.b;

	vec ap = vectorsub(ti->hit, sq->pos);
	normalize_vec(&ap);
	// vec pt = vectorcross(sq->norm, ap);

	if (sq->mat.type == 1)
	{
		double sines =
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
	// printf("%f %f %f \n", sq->pos.x, sq->pos.y, sq->pos.z);
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

void
	mapping(t_stuff *st, t_inter *ti, t_sq *sq)
{
	if (sq->mat.type == 1)
	{
		ti->mat.diffuse = chess_map_sqpl(ti->hit, ti->mat.diffuse, sq->pos, sq->norm);
		return ;
	}
	vec z1 = vectorsub(sq->sqp.v1, ti->hit);
	sq->sqp.w = vectordot(sq->sqp.z2, z1 ) / sq->sqp.d2;
	sq->sqp.h = vectordot(sq->sqp.z3, z1 ) / sq->sqp.d3;
	ti->mat.type -= 10;
	getpixel(st, sq->sqp.w, sq->sqp.h, ti);
}

t_inter
	valid_obja(t_inter *ti)
{
	ti->odir = normalize_v(vectorsub(ti->hit, ti->opos));
	ti->ldir = normalize_v(vectorsub(ti->hit, ti->lpos));
	if (
		((vectordot(ti->n, ti->odir) > 0
		&& vectordot(ti->ldir, ti->n) > 0) ||
		(vectordot(ti->n, ti->odir) < 0
		&& vectordot(ti->ldir, ti->n) < 0)))
	{
		ti->n = vectorscale(-1, ti->n);
	}
	return (*ti);
}

vec	
	valid_obj(t_inter *ti)
{
	double	t1;
	double	t2;
	double	t3;
	double	t4;	

	// printf("HIT %f %f %f \n", ti->hit.x, ti->hit.y, ti->hit.z);
	// printf("OPO %f %f %f \n", ti->opos.x, ti->opos.y, ti->opos.z);
	// printf("LPO %f %f %f \n", ti->lpos.x, ti->lpos.y, ti->lpos.z);
	t1 = calc_dist(ti->opos, ti->hit);
	t2 = calc_dist(ti->opos, vectoradd(ti->hit, ti->n));
	t3 = calc_dist(ti->lpos, ti->hit);
	t4 = calc_dist(ti->lpos, vectoradd(ti->hit, ti->n));
	if (!ti->is_l)
	{
		// printf("LPO %f %f %f \n", ti->lpos.x, ti->lpos.y, ti->lpos.z);
		// printf("OPO %f %f %f \n", ti->opos.x, ti->opos.y, ti->opos.z);
		if (t4 < t3)
		{
			if (t2 < t1)
				return (normalize_v(ti->n));
			else
				return (normalize_v(vectorscale(-1, ti->n)));
		}
		else
		{
			if (t2 > t1)
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
	// if (ti->is_l)
	// 	printf("OPO %f %f %f \n", ti->lpos.x, ti->lpos.y, ti->lpos.z);
	// norm2 = (vectordot(ti->odir, sq.norm) > 0) ? vectorscale(-1, sq.norm) : vectorscale(1, sq.norm);
	// normalize_vec(&sq.norm);
	// den = -vectordot(sq.pos, sq.norm);
	// double a = vectordot(sq.norm, r->start) + den;
	// double b = vectordot(r->dir, sq.norm);
	// if (b == 0)
	// 	b = EPSILON;
	// dist = -(a / b);
	// printf("%f %f \n", ti->t, dist);
	dist = vectordot(vectorsub(sq.pos, r->start), sq.norm) / vectordot(r->dir, sq.norm);
	if (dist < EPSILON || (ti->is_l && dist > ti->t))
		return(invalid_ti(ti));
	ti->hit = vectoradd(r->start, vectorscale(dist, r->dir));
	if (!(fabs(vectordot(vectorsub(ti->hit, sq.pos), sq.sqp.e1)) < pow(sq.len / 2, 2) &&
			fabs(vectordot(vectorsub(ti->hit, sq.pos), sq.sqp.e2)) < pow(sq.len / 2, 2)))
		return(invalid_ti(ti));
	ti->n = sq.norm;
	ti->t = dist;
	// *ti = valid_obja(ti);
	ti->n = valid_obj(ti);
	ti->mat = sq.mat;
	if (sq.mat.type != 0)
		mapping(st, ti, &sq);
	return (*ti);
}

t_inter
	intersect_r_pl(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_pl	pl;
	double	dist;

	pl = *(t_pl *)ptr;
	ti->match = true;

	// normalize_vec(&norm2);
	// den = -vectordot(pl.pos, norm2);
	// double a = vectordot(norm2, r->start) + den;
	// double b = vectordot(r->dir, norm2);
	//if (b == 0)
	//	b = EPSILON;
	//dist = -(a / b);
	// printf("%f %f \n", ti->t, dist);
	dist = vectordot(vectorsub(pl.pos, r->start), pl.norm) / vectordot(r->dir, pl.norm);
	if (dist < EPSILON || (ti->is_l && dist > ti->t))
		return(invalid_ti(ti));
	ti->t = dist;
	ti->hit = vectoradd(r->start, vectorscale(dist, r->dir));
	ti->n = pl.norm;
	// *ti = valid_obja(ti);
	ti->n = valid_obj(ti);
	ti->mat = pl.mat;
	if (pl.mat.type != 0)
		ti->mat.diffuse = chess_map_sqpl(ti->hit, ti->mat.diffuse, pl.pos, pl.norm);
	return (*ti);
}

/*t_inter
	intersect_r_pl(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_pl	pl;
	double	den;
	vec		norm2;
	double	dist;

	(void)st;
	pl = *(t_pl *)ptr;
	ti->match = true;
	normalize_vec(&pl.norm);
	norm2 = pl.norm;
	// norm2 = (vectordot(ti->odir, pl.norm) > 0) ? vectorscale(-1, pl.norm) : vectorscale(1, pl.norm);
	// den = -vectordot(pl.pos, norm2);
	// double a = vectordot(norm2, r->start) + den;
	// double b = vectordot(r->dir, norm2);
	// if (b == 0)
	// 	b = EPSILON;
	// dist = -(a / b);
	dist = vectordot(vectorsub(pl.pos, r->start), pl.norm) / vectordot(r->dir, pl.norm);
	if (dist < EPSILON || dist > ti->t)
		return(invalid_ti(ti));
	ti->t = dist;
	ti->hit = vectoradd(r->start, vectorscale(dist, r->dir));
	ti->n = norm2;
	ti->ldir = vectorscale(-1, ti->ldir);
	ti->n = valid_obj(ti);
	ti->mat = pl.mat;
	return (*ti);
}*/

/*t_inter
	intersect_r_pl(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_pl	pl;
	double	den;
	vec		norm2;

	pl = *(t_pl *)ptr;
	// if (pl.norm.x == 0 && pl.norm.z == 0)
	// {
	// 	pl.norm.y = 0.9999;
	// 	pl.norm.z = 0.0001;
	// }
	// printf("%f %f %f\n", pl.norm.x, pl.norm.y, pl.norm.z);

	normalize_vec(&pl.norm);
	norm2 = pl.norm;
	// norm2 = (vectordot(r->dir, pl.norm) > 0) ? vectorscale(-1, pl.norm) : vectorscale(1, pl.norm);
	den = vectordot(r->dir, norm2);
	if (den < EPSILON)
		return(invalid_ti(ti));
	ti->t = vectordot(vectorsub(pl.pos, r->start), norm2) / den;
	// printf("%f\n", ti->t);
	if (ti->t < EPSILON)
		return(invalid_ti(ti));
	printf("%f \n", ti->t);
	ti->mat = pl.mat;
	ti->hit = vectoradd(r->start, vectorscale(ti->t, r->dir));
	ti->n = norm2;
	ti->n = valid_obj(ti);
	normalize_vec(&ti->n);
	return (*ti);
}*/
