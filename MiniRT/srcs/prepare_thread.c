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
	addray(t_stuff *st, t_var *tv)
{	
	while ((tv->coef > 0) && (tv->level < 10))
	{
		double reflect;
		vec tmp;
		t_inter ti;

		ft_bzero(&ti, sizeof(t_inter));
		ti = find_object(st, &tv->r);
		if (!ti.match)
			break ;
		if (!tv->level)
		{
			tv->rgb[0] *= ti.mat.diffuse.r;
			tv->rgb[1] *= ti.mat.diffuse.g;
			tv->rgb[2] *= ti.mat.diffuse.b;
		}
		calc_light_value(st, tv, &ti);
		tv->coef *= ti.mat.reflection;
		tv->r.start = ti.hit;
		reflect = 2 * vectordot(tv->r.dir, ti.n);
		tmp = vectorscale(reflect, ti.n);
		tv->r.dir = vectorsub(tv->r.dir, tmp);
		normalize_vec(&tv->r.dir);
		tv->level++;
	}
}

void
	put_color(t_stuff *st, t_var *tv, double frag[3])
{
	tv->rgb[0] = st->filt.col[0] * frag[0] * (1 / (SAMPLING * SAMPLING));
	tv->rgb[1] = st->filt.col[1] * frag[1] * (1 / (SAMPLING * SAMPLING));
	tv->rgb[2] = st->filt.col[2] * frag[2] * (1 / (SAMPLING * SAMPLING));
	if (st->filt.sepia)
	{
		double sepia[3];
		sepia[0] = tv->rgb[0];
		sepia[1] = tv->rgb[1];
		sepia[2] = tv->rgb[2];
		tv->rgb[0] = (sepia[0] * 0.393) + (sepia[1] * 0.769) + (sepia[2] * 0.189);
		tv->rgb[1] = (sepia[0] * 0.349) + (sepia[1] * 0.686) + (sepia[2] * 0.168);
		tv->rgb[2] = (sepia[0] * 0.272) + (sepia[1] * 0.534) + (sepia[2] * 0.131);
	}
	*(int *)(st->im.data + ((int)tv->x * 4 + ((int)tv->y * st->im.sizeline))) = set_color(tv->rgb);
}

void
	calc_x(t_stuff *st, t_var *tv)
{
	double	fragmentx;
	double	fragmenty;
	double	frag[3];

	fragmenty = tv->y;
	frag[0] = 0;
	frag[1] = 0;
	frag[2] = 0;
	while (fragmenty < tv->y + 1)
	{
		fragmentx = tv->x;
 		while (fragmentx < tv->x + 1)
		{
			init_var(st, tv, fragmentx, fragmenty);
			addray(st, tv);
			frag[0] += tv->rgb[0];
			frag[1] += tv->rgb[1];
			frag[2] += tv->rgb[2];
			fragmentx += (1 / SAMPLING);
		}
		fragmenty += (1 / SAMPLING);
	}
	put_color(st, tv, frag);
}

void
	*thr_func(void *arg)
{
	t_var			*tv;
	t_thread_data 	*data;
	t_stuff			*st;
	int				x;

	data = (t_thread_data *)arg;
	x = -1;
	while (++x <  data->st->window.width)
	{
		if (!(st = (t_stuff *)malloc(sizeof(t_stuff))))
			return (NULL);
		if (!(tv = (t_var *)malloc(sizeof(t_var))))
			return (0);
		ft_bzero(tv, sizeof(t_var));
		tv->x = x;
		tv->y = data->y;
		st = ft_memcpy(st, data->st, sizeof(t_stuff));
		calc_x(st, tv);
		free(st);
		free(tv);
	}
	return (NULL);
}

int
	draw_scene(t_stuff *st)
{
	pthread_t		*thr;
	t_thread_data	*thr_data;
	double			y;
	int				rc;

	if (!(thr = (pthread_t *)malloc(sizeof(pthread_t) * 6000)))
		return (0);
	if (!(thr_data = (t_thread_data *)malloc(sizeof(t_thread_data) * 6000)))
		return (0);
	ft_bzero(thr, sizeof(pthread_t));
	ft_bzero(thr_data, sizeof(t_thread_data));
  	y = -1;
  	st->waiting = 1;
	while (++y < st->window.height)
  	{
		thr_data[(int)y].st = st;
		thr_data[(int)y].y = y;
		rc = pthread_create(&thr[(int)y], NULL, thr_func, &thr_data[(int)y]);
		if (rc)
			error_message("Create thread error.", st);
 	 }
	y = -1;
	while (++y < st->window.height)
	{
		rc = pthread_join(thr[(int)y], NULL);
		if (rc)
			error_message("Join thread error.", st);
	}
	st->waiting = 0;
	free(thr);
	//free(thr_data);
	return (1);
}
