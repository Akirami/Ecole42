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

void
	rx(vec *v, float x)
{
	v->y = v->y * cos(x) - v->z * sin(x);
	v->z = v->y * sin(x) + v->z * cos(x);
}

void
	ry(vec *v, float y)
{
	v->x = v->x * cos(y) + v->z * sin(y);
	v->z = v->x * -sin(y) + v->z * cos(y);
}

void
	rz(vec *v, float z)
{
	v->x = v->x * cos(z) - v->y * sin(z);
	v->y = v->x * sin(z) + v->y * cos(z);
}

void
	rot(vec *v, vec axe)
{
	rx(v, axe.x);
	ry(v, axe.y);
	rz(v, axe.z);
}

void
	swap_point(vec *p0, vec *p1)
{
	vec	tmp;

	tmp = *p0;
	*p0 = *p1;
	*p1 = tmp;
}