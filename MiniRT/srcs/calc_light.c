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
	calc_pixel(t_inter *ti, t_var *tv, light curr_li, ray lightray)
{
	vec			v1;
	vec			v2;
	double		dot;
	double		lambert;

	lambert = vectordot(lightray.dir, ti->n) * tv->coef;
	tv->rgb[0] += lambert * curr_li.intensity.r * ti->mat.diffuse.r;
	tv->rgb[1] += lambert * curr_li.intensity.g * ti->mat.diffuse.g;
	tv->rgb[2] += lambert * curr_li.intensity.b * ti->mat.diffuse.b;
	v1 = vectorsub(vectorscale(2 * vectordot(lightray.dir, ti->n), ti->n)
		, lightray.dir);
	v2 = vectorsub(tv->r.start, ti->hit);
	v1 = normalize_v(v1);
	v2 = normalize_v(v2);
	dot = vectordot(v1, v2);
	if (!SPECULAR)
		dot = 0;
	if (dot > 0)
	{
		dot = pow(dot, 200);
		tv->rgb[0] += curr_li.intensity.r * dot;
		tv->rgb[1] += curr_li.intensity.g * dot;
		tv->rgb[2] += curr_li.intensity.b * dot;
	}
}

void
	calc_bw(t_var *tv)
{
	double	bw;

	bw = (tv->rgb[0] + tv->rgb[1] + tv->rgb[2]) / 3;
	tv->rgb[0] = bw;
	tv->rgb[1] = bw;
	tv->rgb[2] = bw;
}

void
	calc_light2(t_stuff *st, t_inter *ti, t_var *tv, light *curr_li)
{
	int		k;
	t_inter	ta;
	ray		lightray;
	bool	in_shadow;

	ft_bzero(&ta, sizeof(t_inter));
	lightray.start = ti->hit;
	lightray.dir = normalize_v(vectorscale((1 / ti->t), tv->dist));
	ta.lpos = curr_li->pos;
	ta.opos = ti->opos;
	ta.is_l = true;
	in_shadow = false;
	k = -1;
	while (++k < st->obj_count)
	{
		ta = g_func_ptr[st->objs[k].type](st, st->objs[k].ptr, &ta, &lightray);
		if (ta.match)
		{
			in_shadow = true;
			break ;
		}
	}
	if (!in_shadow)
		calc_pixel(ti, tv, *curr_li, lightray);
	(st->filt.bw) ? calc_bw(tv) : st->filt.bw;
}

void
	calc_light_value(t_stuff *st, t_var *tv, t_inter *ti)
{
	int		j;
	light	curr_li;

	j = -1;
	while (++j < st->li_count)
	{
		curr_li = st->lights[j];
		tv->dist = vectorsub(curr_li.pos, ti->hit);
		if (vectordot(ti->n, tv->dist) > EPSILON) 
		{
			tv->t = sqrt(vectordot(tv->dist, tv->dist));
			if (tv->t > EPSILON)
			{
				calc_light2(st, ti, tv, &curr_li);
			}
		}
	}
}
