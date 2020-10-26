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
	chess_map_cy(vec p, color col, t_cy *cy)
{
	double	theta;
	double	d[2];
	vec		new;
	t_rep	rep;
	color	invcol;

	invcol.r = 1 - col.r;
	invcol.g = 1 - col.g;
	invcol.b = 1 - col.b;
	rep = calc_rep(cy->norm);
	new.x = vectordot(vectorsub(p, cy->pos), vectorscale(cy->radius, rep.v));
	new.y = sqrt(calc_dist(p, cy->pos) * calc_dist(p, cy->pos) - cy->radius
				* cy->radius);
	new.z = vectordot(vectorsub(p, cy->pos), vectorscale(cy->radius, rep.w));
	theta = atan2(new.x, new.z) / (2 * M_PI);
	d[0] = (1 - (theta + 0.5)) * ((2 * M_PI * cy->radius) / (cy->len / 10));
	d[1] = fmod(new.y / cy->len * 10, 2);
	if (((int)d[0] + (int)d[1]) % 2 == 0)
		return (invcol);
	return (col);
}

void
	intersect_circles(double *t, ray *r, t_cy *cy)
{
	double dot;

	dot = vectordot(r->dir, cy->norm);
	if (dot == 0)
		dot = 0.00001;
	t[0] = vectordot(vectorsub(cy->pos, r->start), cy->norm) / dot;
	t[1] = vectordot(vectorsub(cy->top, r->start), cy->norm) / dot;
	if (calc_dist(cy->pos, vectoradd(r->start, vectorscale(t[0],
		r->dir))) > cy->radius)
		t[0] = 200000000;
	if (calc_dist(cy->top, vectoradd(r->start, vectorscale(t[1],
		r->dir))) > cy->radius)
		t[1] = 200000000;
}

t_inter
	calc_ti(t_inter *ti, t_cy *cy, ray *r)
{
	double	z;

	ti->mat = cy->mat;
	ti->hit = vectoradd(r->start, vectorscale(ti->t, r->dir));
	if (cy->mat.type == 1)
		ti->mat.diffuse = chess_map_cy(ti->hit, ti->mat.diffuse, cy);
	z = sqrt(fabs((calc_dist(ti->hit, cy->pos) *
		calc_dist(ti->hit, cy->pos) - cy->radius * cy->radius)));
	cy->norm1 = vectoradd(cy->pos, vectorscale(z, cy->norm));
	if (!cy->capuchon)
		ti->n = vectorsub(ti->hit, cy->norm1);
	else
	{
		ti->n = cy->norm;
		ti->n = valid_obj(ti);
	}
	normalize_vec(&ti->n);
	ti->match = true;
	return (*ti);
}

int
	calc_t(t_cy *cy, ray *r, double *t, double *t2)
{
	t[0] = (-cy->b + sqrt(cy->delta)) / (2 * cy->a);
	t[1] = (-cy->b - sqrt(cy->delta)) / (2 * cy->a);
	if (t[0] < EPSILON && t[1] < EPSILON)
		return (t[0]);
	cy->i = vectorsub(vectoradd(r->start, vectorscale(t[0], r->dir)), cy->pos);
	cy->o = vectorsub(vectoradd(r->start, vectorscale(t[1], r->dir)), cy->pos);
	if (vectordot(cy->i, cy->norm1) > vectordot(cy->norm1, cy->norm1)
		|| vectordot(cy->i, cy->norm1) < 0)
		t[0] = 200000000;
	if (vectordot(cy->o, cy->norm1) > vectordot(cy->norm1, cy->norm1)
		|| vectordot(cy->o, cy->norm1) < 0)
		t[1] = 200000000;
	intersect_circles(t2, r, cy);
	if (t2[0] < t[0] && t2[0] < t[1])
	{
		t[0] = t2[0];
		cy->capuchon = 1;
	}
	if (t2[1] < t[0] && t2[1] < t[1])
	{
		t[1] = t2[1];
		cy->capuchon = 1;
	}
	return ((t[0] < t[1]) ? t[0] : t[1]);
}

t_inter
	intersect_r_cy(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_cy	cy;
	double	t[2];
	double	t2[2];

	(void)st;
	cy = *(t_cy *)ptr;
	ti->match = true;
	normalize_vec(&cy.norm);
	cy.top = vectoradd(cy.pos, vectorscale(cy.len, cy.norm));
	cy.hit[0] = vectorsub(r->start, cy.pos);
	cy.hit[1] = vectorsub(cy.hit[0],
		vectorscale(vectordot(cy.hit[0], cy.norm), cy.norm));
	cy.norm1 = vectorsub(cy.top, cy.pos);
	cy.hit[2] = vectorsub(r->dir,
		vectorscale(vectordot(r->dir, cy.norm), cy.norm));
	cy.a = vectordot(cy.hit[2], cy.hit[2]);
	cy.b = 2 * vectordot(cy.hit[2], cy.hit[1]);
	cy.c = vectordot(cy.hit[1], cy.hit[1]) - (cy.radius * cy.radius);
	cy.delta = cy.b * cy.b - (4 * cy.a * cy.c);
	if ((cy.a == 0 || cy.delta < EPSILON))
		return (invalid_ti(ti));
	ti->t = calc_t(&cy, r, t, t2);
	if (ti->t < EPSILON || ti->t == 200000000)
		return (invalid_ti(ti));
	return (calc_ti(ti, &cy, r));
}
