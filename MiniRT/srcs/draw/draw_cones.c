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
	check_dist_co(t_inter *ti, t_co *co, ray *r, int8_t ci)
{
	double	d;
	double	t;

	t = co->t;
	if (t == INF)
		return (invalid_ti(ti));
	if (t > EPSILON)
	{
		ti->hit = vectoradd(r->start, vectorscale(t, r->dir));
		d = calc_dist(ti->hit, co->pos) / cos((co->angl / 2) * M_PI / 180);
		ti->n = vectoradd(co->pos, vectorscale(d, co->dir));
		ti->n = normalize_v(vectorsub(ti->hit, ti->n));
		ti->n = ((vectordot(r->dir, ti->n) > 0 && ci == 1) ?
				vectorscale(-1, ti->n) : ti->n);
		ti->t = t;
		ti->mat = co->mat;
		return (*ti);
	}
	return (invalid_ti(ti));
}

t_inter
	intersect_co2(t_inter *ti, ray *r, t_co *co, double *k)
{
	double	t[2];
	vec		p[2];
	int8_t	ci;

	co->pos1 = vectoradd(co->pos, vectorscale(co->height, co->dir));
	t[0] = (-k[2] + sqrt(k[0])) / (2 * k[1]);
	t[1] = (-k[2] - sqrt(k[0])) / (2 * k[1]);
	p[0] = vectoradd(r->start, vectorscale(t[0], r->dir));
	p[1] = vectoradd(r->start, vectorscale(t[1], r->dir));
	co->rad = co->height * tan((co->angl / 2) * M_PI / 180);
	if (((vectordot(vectorsub(p[0], co->pos), co->dir) < 0)
		|| (vectordot(vectorsub(p[0], co->pos), vectorsub(co->pos1,
			co->pos)) > vectordot(vectorsub(co->pos1, co->pos),
			vectorsub(co->pos1, co->pos))) || t[0] < 1))
		t[0] = INF;
	if (((vectordot(vectorsub(p[1], co->pos), co->dir) < 0)
		|| (vectordot(vectorsub(p[1], co->pos), vectorsub(co->pos1,
			co->pos)) > vectordot(vectorsub(co->pos1, co->pos),
			vectorsub(co->pos1, co->pos)))) || t[1] < 1)
		t[1] = INF;
	ci = (t[0] != INF && t[1] == INF ? 1 : 0);
	co->t = (t[0] < t[1]) ? t[0] : t[1];
	return (check_dist_co(ti, co, r, ci));
}

t_inter
	intersect_r_co(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	double	k[4];
	double	a;
	t_co	co;

	co = *(t_co *)ptr;
	ti->match = true;
	(void)st;
	co.dp = vectorsub(r->start, co.pos);
	a = co.angl / 2 * M_PI / 180;
	co.dir = normalize_v(co.dir);
	k[1] = cos(a) * cos(a) * vectordot(vectorsub(r->dir,
				vectorscale(vectordot(r->dir, co.dir), co.dir)),
			vectorsub(r->dir, vectorscale(vectordot(r->dir, co.dir), co.dir)))
		- sin(a) * sin(a) * pow(vectordot(r->dir, co.dir), 2);
	k[2] = 2 * pow(cos(a), 2) * vectordot(vectorsub(r->dir,
				vectorscale(vectordot(r->dir, co.dir), co.dir)),
			vectorsub(co.dp, vectorscale(vectordot(co.dp, co.dir), co.dir)))
		- 2 * pow(sin(a), 2) * vectordot(r->dir, co.dir)
		* vectordot(co.dp, co.dir);
	k[3] = pow(cos(a), 2) * vectordot(vectorsub(co.dp,
				vectorscale(vectordot(co.dp, co.dir), co.dir)),
			vectorsub(co.dp, vectorscale(vectordot(co.dp, co.dir), co.dir)))
		- pow(sin(a), 2) * pow(vectordot(co.dp, co.dir), 2);
	k[0] = k[2] * k[2] - 4 * k[1] * k[3];
	return ((k[0] < EPSILON) ? invalid_ti(ti) : intersect_co2(ti, r, &co, k));
}
