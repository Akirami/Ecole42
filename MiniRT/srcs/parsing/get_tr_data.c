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

char
	*truncate_str(char *str)
{
	while (str && *str && ft_strchr("\t\v\n\f\r ", *str))
		str++;
	return (str);
}

int
	get_triangles_data2(char *str, t_tr *tr)
{
	int			j;
	char		*tmp;
	int			color[3];

	str = get_color(str, color);
	if (str == NULL)
		return (0);
	double_to_rgb(&tr->mat.diffuse, color);
	str = truncate_str(str);
	j = calc_i_double(str);
	if (str && *str)
	{
		tmp = ft_strsub(str, 0, j);
		tr->mat.reflection = ft_atof(tmp);
		free(tmp);
		str = &(*(str + j));
	}
	else
		tr->mat.reflection = 0;
	if (*str && str)
		tr->mat.type = ft_atof(str);
	return (1);
}

int
	get_triangles_data(char *str, void **ptr, t_stuff *st)
{
	t_tr		*tr;
	static int	i;
	double		coor[3];

	if (!(tr = malloc(sizeof(t_tr))))
		return (-1);
	ft_bzero(tr, sizeof(t_tr));
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &tr->p0);
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &tr->p1);
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &tr->p2);
	get_triangles_data2(str, tr);
	*ptr = tr;
	st->tr_count = ++i;
	return (1);
}

int
	check_triangles_data(char *str, void **ptr, t_stuff *st)
{
	int i;
	int res;

	res = 1;
	i = 0;
	str += 2;
	str = truncate_str(str);
	if (!ft_strchr("0123456789-.", *str))
		res *= error_message("tr contains invalide data.", st);
	if (get_triangles_data(str, ptr, st) != 1)
		res *= error_message("tr contains wrong point(s) or color(s).", st);
	return (res);
}
