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

t_inter
	invalid_ti(t_inter *ti)
{
	ti->match = false;
	return (*ti);
}

void
	prepare_tr(t_tr *tr)
{
	tr->v0v1 = vectorsub(tr->p1, tr->p0);
	tr->v0v2 = vectorsub(tr->p2, tr->p0);
	tr->v1v2 = vectorsub(tr->p2, tr->p1);
	tr->n = vectorcross(tr->v0v1, tr->v0v2);
	tr->uu = vectordot(tr->v0v1, tr->v0v1);
	tr->uv = vectordot(tr->v0v1, tr->v0v2);
	tr->vv = vectordot(tr->v0v2, tr->v0v2);
	tr->d = tr->uv * tr->uv - tr->uu * tr->vv;
}

t_inter
	calc_tr_ti(t_inter *ti, t_tr tr, double t)
{
	ti->t = t;
	ti->n = tr.n;
	normalize_vec(&ti->n);
	ti->n = valid_obj(ti);
	ti->mat = tr.mat;
	if (tr.mat.type != 0)
		ti->mat.diffuse = chess_map_sqpl(ti->hit,
			ti->mat.diffuse, tr.p0, ti->n);
	return (*ti);
}

t_inter
	intersect_r_tr(t_stuff *st, void *ptr, t_inter *ti, ray *ra)
{
	t_tr	tr;
	double	wv_wu[2];
	double	r[2];
	double	a;
	double	t;

	(void)st;
	ti->match = true;
	tr = *(t_tr *)ptr;
	prepare_tr(&tr);
	a = vectordot(ra->start, tr.n) - (vectordot(tr.n, tr.p0));
	t = -(a / vectordot(ra->dir, tr.n));
	if (t < EPSILON || (!ti->is_l && t > ti->t))
		return (invalid_ti(ti));
	ti->hit = vectoradd(ra->start, vectorscale(t, ra->dir));
	wv_wu[0] = vectordot(vectorsub(ti->hit, tr.p0), tr.v0v1);
	wv_wu[1] = vectordot(vectorsub(ti->hit, tr.p0), tr.v0v2);
	r[0] = (tr.uv * wv_wu[1] - tr.vv * wv_wu[0]) / tr.d;
	if (r[0] < 0 || r[0] > 1)
		return (invalid_ti(ti));
	r[1] = (tr.uv * wv_wu[0] - tr.uu * wv_wu[1]) / tr.d;
	if (r[1] < 0 || (r[0] + r[1] > 1))
		return (invalid_ti(ti));
	return (calc_tr_ti(ti, tr, t));
}
