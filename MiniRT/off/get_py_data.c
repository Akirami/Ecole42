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

void
	generate_pyramid(t_py *py)
{
	t_rep	rep;
	t_vec3d	h;
	t_vec3d l;

	rep = calc_rep(py->dir);
	py->base.dir = rep.u;
	py->base.pos = py->pos;
	py->base.height = py->height;
	py->t1.p1 = vector_add(py->pos, vector_mul(rep.u, py->width));
	py->t2.p1 = py->t1.p1;
	py->t3.p1 = py->t1.p1;
	py->t4.p1 = py->t1.p1;
	h = vector_sub(vector_add(py->pos, vector_mul(rep.v, py->height / 2)),
			py->pos);
	l = vector_sub(vector_add(py->pos, vector_mul(rep.w, py->height / 2)),
			py->pos);
	py->t1.p2 = vector_add(vector_add(h, l), py->pos);
	py->t1.p3 = vector_add(vector_add(vector_mul(h, -1), l), py->pos);
	py->t4.p3 = py->t1.p3;
	py->t2.p2 = py->t1.p2;
	py->t2.p3 = vector_add(vector_add(h, vector_mul(l, -1)), py->pos);
	py->t3.p2 = py->t2.p3;
	py->t3.p3 = vector_add(vector_add(vector_mul(h, -1), vector_mul(l, -1)),
									py->pos);
	py->t4.p2 = py->t3.p3;
}

void
	obj_py(char **line, t_obj *obj)
{
	t_f		*new_form;
	t_py	*new;

	if (!*line || !line[1] || !line[2] || !line[3] || !line[4] || !line[5])
		ft_puterror(ERR_NOT_ENOUGH_PY, 1, free_all(NULL, line, obj));
	if (!(new = ft_calloc(1, sizeof(t_py))))
		ft_puterror(ERR_ALLOC_PY, 1, free_all(NULL, line, obj));
	new->pos = set_vec3d(line, obj, 1);
	new->dir = set_vec3d(line, obj, 2);
	check_dir_range(new->dir, line, obj);
	new->height = ft_atod(line, NULL, obj, 3);
	new->width = ft_atod(line, NULL, obj, 4);
	if (new->height <= 0.0 || new->width <= 0.0)
		ft_puterror(ERR_HEIGHT_RANGE, 1, free_all(NULL, line, obj));
	new->rgb = set_rgb(line, obj, 5);
	new->reflect = (line[6] ? ft_atod(line, NULL, obj, 6) : 0);
	if (new->reflect < 0.0 || new->reflect > 1.0)
		ft_puterror(ERR_REFLECT_RANGE, 1, free_all(NULL, line, obj));
	generate_pyramid(new);
	if (!(new_form = malloc(sizeof(t_f))))
		ft_puterror(ERR_ALLOC_PY, 1, free_all(NULL, line, obj));
	new_form->f = new;
	new_form->next = NULL;
	add_new_form(obj, new_form, line);
}

void	pre_calc_py(t_py *py)
{
	pre_calc_sq((t_sq*)&py->base);
	pre_calc_tr((t_tr*)&py->t1);
	pre_calc_tr((t_tr*)&py->t2);
	pre_calc_tr((t_tr*)&py->t3);
	pre_calc_tr((t_tr*)&py->t4);
}

int8_t	intersect_py(const t_py *py, t_ray *ray)
{
	int8_t	ret;

	ret = 0;
	ret += intersect_sq((t_sq*)&py->base, ray);
	ret += intersect_tr((t_tr*)&py->t1, ray);
	ret += intersect_tr((t_tr*)&py->t2, ray);
	ret += intersect_tr((t_tr*)&py->t3, ray);
	ret += intersect_tr((t_tr*)&py->t4, ray);
	return (ret);
}
