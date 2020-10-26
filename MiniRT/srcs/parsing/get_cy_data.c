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

bool
	check_dir(vec dir)
{
	if (dir.x == 0 && dir.y == 0 && dir.z == 0)
		return (false);
	return (true);
}

char
	*get_cy_diam(char *str, t_cy *cy, t_stuff *st)
{
	int			j;
	char		*tmp;
	char		*tmp2;

	str = truncate_str(str);
	j = calc_i_double(str);
	tmp = ft_strsub(str, 0, j);
	cy->radius = ft_atof(tmp) / 2;
	if (cy->radius < 1)
		error_message("Cylender has wrong diameter.", st);
	free(tmp);
	str = &(*(str + j));
	while (ft_strchr("\t\v\n\f\r ", *str))
		str++;
	j = calc_i_double(str);
	tmp2 = ft_strsub(str, 0, j);
	cy->len = ft_atof(tmp2);
	if (cy->len < 1)
		error_message("Cylender has wrong lenght.", st);
	free(tmp2);
	str = &(*(str + j));
	return (str);
}

char
	*get_cylender_data2(char *str, t_cy *cy, t_stuff *st)
{
	int			color[3];
	int			j;
	char		*tmp;

	str = get_cy_diam(str, cy, st);
	if (str == NULL)
		return (0);
	str = get_color(str, color);
	if (str == NULL)
		return (0);
	double_to_rgb(&cy->mat.diffuse, color);
	str = truncate_str(str);
	j = calc_i_double(str);
	if (str && *str)
	{
		tmp = ft_strsub(str, 0, j);
		cy->mat.reflection = ft_atof(tmp);
		free(tmp);
		str = &(*(str + j));
	}
	if (str && *str)
		cy->mat.type = ft_atof(str);
	if (cy->mat.type > 1)
		error_message("Cylender texture type out of range.", st);
	return (str);
}

int
	get_cylender_data(char *str, void **ptr, t_stuff *st)
{
	int			res;
	t_cy		*cy;
	double		coor[3];
	static int	i;

	if (!(cy = malloc(sizeof(t_cy))))
		return (-1);
	ft_bzero(cy, sizeof(t_cy));
	res = 1;
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &cy->pos);
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &cy->norm);
	if (!check_dir(cy->norm))
		error_message("Invalid cylender normal.", st);
	str = get_cylender_data2(str, cy, st);
	st->cy_count = ++i;
	*ptr = cy;
	return (res);
}

int
	check_cylenders_data(char *str, void **ptr, t_stuff *st)
{
	int res;

	res = 1;
	str += 2;
	str = truncate_str(str);
	if (!ft_strchr("0123456789-.", *str))
		res *= error_message("Cylender contains invalide data.", st);
	if (get_cylender_data(str, ptr, st) != 1)
		res *= error_message("Cylender contains \
			wrong point(s) or color(s).", st);
	return (res);
}
