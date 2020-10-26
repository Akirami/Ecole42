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
	mapping_sq(t_stuff *st, t_inter *ti, t_sq *sq)
{
	vec	z1;

	if (sq->mat.type == 1)
	{
		ti->mat.diffuse = chess_map_sqpl(ti->hit,
			ti->mat.diffuse, sq->pos, sq->norm);
		return ;
	}
	z1 = vectorsub(sq->sqp.v1, ti->hit);
	sq->sqp.w = vectordot(sq->sqp.z2, z1) / sq->sqp.d2;
	sq->sqp.h = vectordot(sq->sqp.z3, z1) / sq->sqp.d3;
	ti->mat.type -= 10;
	getpixel(st, sq->sqp.w, sq->sqp.h, ti);
}

void
	prepare_sq_map(t_sq *sq)
{
	vec v2;
	vec v3;
	vec v4;

	sq->sqp.v1 = vectoradd(vectoradd(sq->pos, sq->sqp.e1),
		vectorscale(-1, sq->sqp.e2));
	v2 = vectoradd(vectoradd(sq->pos, sq->sqp.e1), sq->sqp.e2);
	v3 = vectoradd(vectoradd(sq->pos, vectorscale(-1, sq->sqp.e1)),
		vectorscale(-1, sq->sqp.e2));
	v4 = vectoradd(vectoradd(sq->pos, vectorscale(-1, sq->sqp.e1)),
		sq->sqp.e2);
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

	u = normalize_v(sq->norm);
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
	sq->sqp.e1 = vectorsub(vectoradd(sq->pos,
		vectorscale(sq->len / 2, v)), sq->pos);
	sq->sqp.e2 = vectorsub(vectoradd(sq->pos,
		vectorscale(sq->len / 2, w)), sq->pos);
	sq->sqp.de1 = vectordot(sq->sqp.e1, sq->sqp.e1);
	sq->sqp.de2 = vectordot(sq->sqp.e2, sq->sqp.e2);
	prepare_sq_map(sq);
}
