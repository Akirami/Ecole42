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
	generate_tr(t_py *py, int l)
{
	t_rep	rep;

	rep = calc_rep(py->norm);
}

int
	check_pyra_data(char *str, t_stuff *st, int j)
{
	int		res;
	int		k;

	k = -1;
	res = 1;
	while (++k < 3)
	{
		res *= (*g_objs_ptr[2])(str, &st->objs[j].ptr, st);
		if (res == 0)
			error_message("Wrong pyramide datas.\n", st);
		st->objs[j].type = 3;
		generate_tr((t_py *)st->objs[j].ptr, k);
		prepare_tr((t_tr *)st->objs[j].ptr);
		j++;
	}
	return (j);
}

int
	check_cubes_data(char *str, t_stuff *st, int j)
{
	int		res;
	int		k;

	k = -1;
	res = 1;
	while (++k < 6)
	{
		res *= (*g_objs_ptr[3])(str, &st->objs[j].ptr, st);
		if (res == 0)
			error_message("Wrong cube datas.\n", st);
		st->objs[j].type = 3;
		generate_cu((t_sq *)st->objs[j].ptr, k);
		prepare_sq((t_sq *)st->objs[j].ptr);
		j++;
	}
	return (j);
}
