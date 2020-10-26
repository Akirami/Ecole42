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

color
	h_to_rgb(const int hex)
{
	color rgb;

	rgb.r = (hex >> 16) & 0xFF;
	rgb.g = (hex >> 8) & 0xFF;
	rgb.b = (hex) & 0xFF;
	return (rgb);
}

void
	n_vec(double a, double b, double c, vec *v)
{
	v->x = a;
	v->y = b;
	v->z = c;
}

void
	ft_swap(double *x, double *y)
{
	double	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

unsigned int
	rgb_to_hex(int rgb[4])
{
	unsigned int xrgb;

	xrgb = ((rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3]);
	return (xrgb);
}

double
	calc_dist(vec p0, vec p1)
{
	double result;

	result = sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2) + pow(p1.z - p0.z, 2));
	return (result);
}
