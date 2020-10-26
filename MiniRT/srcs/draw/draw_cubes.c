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

t_rep
	calc_rep(const vec dir)
{
	t_rep rep;

	rep.u = normalize_v(dir);
	n_vec(0, 1, 0, &rep.v);
	n_vec(-1, 0, 0, &rep.w);
	if (rep.u.x == 0 && rep.u.z == 0)
		n_vec(0, 0, -1, &rep.v);
	else
	{
		rep.v = normalize_v(vectorsub(rep.v,
			vectorscale(vectordot(rep.u, rep.v), rep.u)));
		rep.w = normalize_v(vectorcross(rep.v, rep.u));
	}
	return (rep);
}

void
	pre_calc_cu(t_cu *cu)
{
	prepare_sq((t_sq*)&cu->sq[0]);
	(cu->mat.type == 9) ? cu->sq[0].mat.type = 17 : cu->mat.type;
	prepare_sq((t_sq*)&cu->sq[1]);
	(cu->mat.type == 9) ? cu->sq[0].mat.type = 18 : cu->mat.type;
	prepare_sq((t_sq*)&cu->sq[2]);
	(cu->mat.type == 9) ? cu->sq[0].mat.type = 19 : cu->mat.type;
	prepare_sq((t_sq*)&cu->sq[3]);
	(cu->mat.type == 9) ? cu->sq[0].mat.type = 20 : cu->mat.type;
	prepare_sq((t_sq*)&cu->sq[4]);
	(cu->mat.type == 9) ? cu->sq[0].mat.type = 21 : cu->mat.type;
	prepare_sq((t_sq*)&cu->sq[5]);
	(cu->mat.type == 9) ? cu->sq[0].mat.type = 22 : cu->mat.type;
}

void
	generate_square(t_sq *sq, vec norm, int r)
{
	t_rep	tmp;

	sq->norm = norm;
	sq->pos = vectoradd(sq->pos, vectorscale(sq->len / 2, sq->norm));
	if (r)
	{
		tmp = calc_rep(norm);
		sq->angle = (acos(vectordot(tmp.v,
			normalize_v(sq->norm))) * 180 / M_PI) * r;
	}
}

/*
** 17 right
** 18 bottom
** 19 left
** 20 back
** 21 fromt
** 22 top a retourner
*/

void
	generate_cu2(t_sq *sq, int l, t_rep rep)
{
	if (l == 3)
	{
		generate_square(sq, vectorscale(-1, rep.u), 0);
		(sq->mat.type == 9) ? sq->mat.type = 18 : sq->mat.type;
	}
	else if (l == 4)
	{
		generate_square(sq, vectorscale(-1, rep.v), 0);
		(sq->mat.type == 9) ? sq->mat.type = 20 : sq->mat.type;
	}
	else if (l == 5)
	{
		generate_square(sq, vectorscale(-1, rep.w), -1);
		(sq->mat.type == 9) ? sq->mat.type = 17 : sq->mat.type;
	}
}

void
	generate_cu(t_sq *sq, int l)
{
	t_rep	rep;

	rep = calc_rep(sq->norm);
	if (l == 0)
	{
		generate_square(sq, rep.u, 0);
		(sq->mat.type == 9) ? sq->mat.type = 22 : sq->mat.type;
	}
	else if (l == 1)
	{
		generate_square(sq, rep.v, 0);
		(sq->mat.type == 9) ? sq->mat.type = 21 : sq->mat.type;
	}
	else if (l == 2)
	{
		generate_square(sq, rep.w, 1);
		(sq->mat.type == 9) ? sq->mat.type = 19 : sq->mat.type;
	}
	generate_cu2(sq, l, rep);
}
