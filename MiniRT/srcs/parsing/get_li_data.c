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
	*get_li_ratio(t_stuff *stuff, char *str, int i)
{
	int			j;
	char		*tmp;

	j = 0;
	str = truncate_str(str);
	j = calc_i_double(str);
	tmp = ft_strsub(str, 0, j);
	if (!(*tmp))
		error_message("Wrong lights data.", stuff);
	stuff->obj.lights[i].ratio = ft_atof(tmp);
	free(tmp);
	str = &(*(str + j));
	str = truncate_str(str);
	return (str);
}

int
	get_light_data(char *str, t_stuff *st)
{
	int			res;
	static int	i;
	double		coor[3];

	res = 1;
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &st->obj.lights[i].pos);
	str = get_li_ratio(st, str, i);
	if (str == NULL)
		return (0);
	str = get_color(str, st->obj.lights[i].color);
	if (str == NULL)
		return (0);
	st->obj.lights[i].intensity.r = (double)st->obj.lights[i].color[0] /
		255 * st->obj.lights[i].ratio;
	st->obj.lights[i].intensity.g = (double)st->obj.lights[i].color[1] /
		255 * st->obj.lights[i].ratio;
	st->obj.lights[i].intensity.b = (double)st->obj.lights[i].color[2] /
		255 * st->obj.lights[i].ratio;
	st->li_count = ++i;
	return (res);
}

int
	check_light_data(char *str, t_stuff *st)
{
	int i;
	int res;

	res = 1;
	i = 0;
	str++;
	str = truncate_str(str);
	if (!ft_strchr("0123456789-.", *str))
		res *= error_message("Lights contains invalide data.", st);
	if (get_light_data(str, st) != 1)
		res *= error_message("Lights contains wrong point(s) or color(s).", st);
	return (res);
}
