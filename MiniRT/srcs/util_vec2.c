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

vec
	normalize_v(vec v)
{
	double	len;

	len = sqrtf(fabs(vectordot(v, v)));
	v.x = v.x / len;
	v.y = v.y / len;
	v.z = v.z / len;
	return (v);
}

void
	normalize_vec(vec *v)
{
	double	len;

	len = sqrtf(fabs(vectordot(*v, *v)));
	v->x = v->x / len;
	v->y = v->y / len;
	v->z = v->z / len;
}

void
	double_to_rgb(color *c, int rgb[3])
{
	c->r = (double)rgb[0] / 255;
	c->g = (double)rgb[1] / 255;
	c->b = (double)rgb[2] / 255;
}

void
	double_to_vec(double coor[3], vec *v)
{
	v->x = coor[0];
	v->y = coor[1];
	v->z = coor[2];
}

vec
	vectorcross(vec v1, vec v2)
{
	vec	result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}
