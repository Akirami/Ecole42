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

void		intersect_circles(double *t, t_vector *ray, t_type *cylinder)
{
	double dot;	
	if ((dot = scalar(ray[1], cylinder->dir)) == 0)
		dot = 0.00000001;
	t[0] = scalar(sub_vec(cylinder->pos, ray[0]), cylinder->dir) / dot;
	t[1] = scalar(sub_vec(cylinder->pos1, ray[0]), cylinder->dir) / dot;
	if (norme(cylinder->pos, add_vec(ray[0], v_product_c(t[0], ray[1]))) > cylinder->radius)
		t[0] = INF;
	if (norme(cylinder->pos1, add_vec(ray[0], v_product_c(t[1], ray[1]))) > cylinder->radius)
		t[1] = INF;
}

double		int_cy2(t_vector *ray, t_type *cylinder, t_vector *o, double *k)
{
	double	t[2];
	double	t2[2];	
	cylinder->fov = 0;
	t[0] = (-k[2] + sqrt(k[0])) / (2 * k[1]);
	t[1] = (-k[2] - sqrt(k[0])) / (2 * k[1]);
	o[5] = sub_vec(add_vec(ray[0], v_product_c(t[0], ray[1])), cylinder->pos);
	o[6] = sub_vec(add_vec(ray[0], v_product_c(t[1], ray[1])), cylinder->pos);
	if (scalar(o[5], o[3]) > scalar(o[3], o[3]) || scalar(o[5], o[3]) < 0)
		t[0] = INF;
	if (scalar(o[6], o[3]) > scalar(o[3], o[3]) || scalar(o[6], o[3]) < 0)
		t[1] = INF;
	intersect_circles(t2, ray, cylinder);
	if (t2[0] < t[0] && t2[0] < t[1])
	{
		t[0] = t2[0];
		cylinder->fov = 1;
	}
	if (t2[1] < t[0] && t2[1] < t[1])
	{
		t[1] = t2[1];
		cylinder->fov = 1;
	}
	return (t[0] < t[1] ? t[0] : t[1]);
}

void
	intersect_cylinder(double *t, t_vector *ray, t_type *cylinder)
{
	t_vector	o[7];
	double		k[4];	
	o[2] = sub_vec(ray[0], cylinder->pos);
	o[1] = normalization(cylinder->dir);
	o[4] = sub_vec(o[2], v_product_c(scalar(o[2], o[1]), o[1]));
	cylinder->pos1 = add_vec(cylinder->pos,
	v_product_c(cylinder->height, o[1]));
	o[3] = sub_vec(cylinder->pos1, cylinder->pos);
	o[0] = sub_vec(ray[1], v_product_c(scalar(ray[1], o[1]), o[1]));
	k[1] = scalar(o[0], o[0]);
	k[2] = 2 * scalar(o[0], o[4]);
	k[3] = scalar(o[4], o[4]) - cylinder->radius * cylinder->radius;
	k[0] = k[2] * k[2] - 4 * k[1] * k[3];
	if (k[0] < 0)
		*t = INF;
	else
		*t = int_cy2(ray, cylinder, o, k);
}

int			cylinder_color(t_vector *ray, t_scene *s, t_vector p, t_type *c)
{
	double		i[3];
	int			g;
	t_vector	l[2];
	t_type		*x;	g = 
	add_color(mul_color(c->color, s->a_light), s->al_color, s->a_light);
	i[2] = sqrt(norme(p, c->pos) * norme(p, c->pos) - c->radius * c->radius);
	l[1] = normalization(sub_vec(p, add_vec(c->pos,
							v_product_c(i[2], c->dir))));
	l[1] = (c->fov == 1 ? c->dir : l[1]);
	l[1] = (scalar(ray[1], l[1]) > 0 ? v_product_c(-1, l[1]) : l[1]);
	x = s->objects;
	while (x)
	{
		if (x->name == 2 || (x->name == 8 && p_line(x, p)))
		{
			l[1] = (c->fov == 1 ? side_test(l[1], ray, p, x) : l[1]);
			i[0] = mul_color(x->color, x->ratio);
			if (((i[1] = scalar(l[1], normalization(sub_vec(x->pos, p)))) > 0)
			&& (test_shadow(x, p, s) == 0))
				g = add_color(g, i[0], i[1]);
		}
		x = x->next;
	}
	return (g);
}

































t_inter
	intersect_circles(double *t, ray *r, t_inter *ti, t_cy *cy)
{
	double dot;	

	dot = vectordot(r->dir, cy->norm);
	if (dot < 0)
		return(invalid_ti(ti));
	t[0] = vectordot(vectorsub(cy->pos, r->start),
	cy->norm) / dot;
	t[1] = vectordot(vectorsub(cy->pos1, r->start),
	cy->norm) / dot;
	if (calc_dist(cy->pos, vectoradd(r->start,
	vectorscale(t[0], r->dir))) > cy->radius)
		return(invalid_ti(ti));
	if (calc_dist(cy->pos1, vectoradd(r->start,
	vectorscale(t[1], r->dir))) > cy->radius)
		return(invalid_ti(ti));
	return (*ti);
}

t_inter
	int_cy2(ray *r, t_cy *cy, t_inter *ti, vec *o, double *k)
{
	double	t[2];
	double	t2[2];	

	cy->fov = 0;
	t[0] = (-k[2] + sqrt(k[0])) / (2 * k[1]);
	t[1] = (-k[2] - sqrt(k[0])) / (2 * k[1]);
	o[5] = vectorsub(vectoradd(r->start, vectorscale(t[0], r->dir)), cy->pos);
	o[6] = vectorsub(vectoradd(r->start, vectorscale(t[1], r->dir)), cy->pos);
	if (vectordot(o[5], o[3]) > vectordot(o[3], o[3]) || vectordot(o[5], o[3]) < 0)
		return(invalid_ti(ti));
	if (vectordot(o[6], o[3]) > vectordot(o[3], o[3]) || vectordot(o[6], o[3]) < 0)
		return(invalid_ti(ti));
	*ti = intersect_circles(t2, r, ti, cy);
	if (t2[0] < t[0] && t2[0] < t[1])
	{
		t[0] = t2[0];
		cy->fov = 1;
	}
	if (t2[1] < t[0] && t2[1] < t[1])
	{
		t[1] = t2[1];
		cy->fov = 1;
	}
	ti->t = (t[0] < t[1]) ? t[0] : t[1];
	ti->hit = vectoradd(r->start, vectorscale(ti->t, r->dir));
	return (*ti);
}

t_inter
	intersect_r_cy(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	vec	o[7];
	double		k[4];	
	t_cy		cy;

	cy = *(t_cy *)ptr;
	ti->match = true;
	normalize_vec(&cy.norm);

	o[2] = vectorsub(r->start, cy.pos);
	cy.norm = normalize_v(cy.norm);
	o[4] = vectorsub(o[2], vectorscale(vectordot(o[2], cy.norm), cy.norm));
	cy.pos1 = vectoradd(cy.pos, vectorscale(cy.len, cy.norm));
	o[3] = vectorsub(cy.pos1, cy.pos);
	o[0] = vectorsub(r->dir, vectorscale(vectordot(r->dir, cy.norm), cy.norm));
	k[1] = vectordot(o[0], o[0]);
	k[2] = 2 * vectordot(o[0], o[4]);
	k[3] = vectordot(o[4], o[4]) - cy.radius * cy.radius;
	k[0] = k[2] * k[2] - 4 * k[1] * k[3];
	if (k[0] < 0)
		return(invalid_ti(ti));
	ti->n = cy.norm;
	ti->mat = cy.mat;
	int_cy2(r, &cy, ti, o, k);
	printf("%f \n", ti->t);
	// printf("RTRTRT %f %f %f \n", cy.mat.diffuse.r, cy.mat.diffuse.g, cy.mat.diffuse.b);
	// printf("RTRTRT %f %f %f \n", ti->hit.x, ti->hit.y, ti->hit.z);
	return (*ti);
}

/*int
	cy_color(ray *r, t_scene *s, vec p, t_type *c)
{
	double		i[3];
	int			g;
	vec	l[2];

	t_type *x;	

	g = add_color(mul_color(c->color, s->a_light), s->al_color, s->a_light);
	i[2] = sqrt(calc_dist(p, c->pos) * calc_dist(p, c->pos) - c->radius * c->radius);
	l[1] = normalize_v(vectorsub(p, vectoradd(c->pos, vectorscale(i[2], c->dir))));
	l[1] = (c->fov == 1 ? c->dir : l[1]);
	l[1] = (vectordot(r->dir, l[1]) > 0 ? vectorscale(-1, l[1]) : l[1]);
	x = s->objects;
	while (x)
	{
		if (x->name == 2 || (x->name == 8 && p_line(x, p)))
		{
			l[1] = (c->fov == 1 ? side_test(l[1], r, p, x) : l[1]);
			i[0] = mul_color(x->color, x->ratio);
			if (((i[1] = vectordot(l[1], normalize_v(vectorsub(x->pos, p)))) > 0)
			&& (test_shadow(x, p, s) == 0))
				g = add_color(g, i[0], i[1]);
		}
		x = x->next;
	}
	return (g);
}*/