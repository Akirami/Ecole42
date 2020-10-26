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

double
	vectordot(vec v1, vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

vec
	vectorsub(vec v1, vec v2)
{
	vec result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

vec
	vectoradd(vec v1, vec v2)
{
	vec result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

vec
	vectoradd3(vec v1, vec v2, vec v3)
{
	vec result;

	result.x = v1.x + v2.x + v3.x;
	result.y = v1.y + v2.y + v3.y;
	result.z = v1.z + v2.z + v3.z;
	return (result);
}

vec
	vectorscale(double c, vec v)
{
	vec result;

	result.x = v.x * c;
	result.y = v.y * c;
	result.z = v.z * c;
	return (result);
}