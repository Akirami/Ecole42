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

int
	calc_i_double(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_strchr("0123456789.", str[i]))
		i++;
	return (i);
}

char
	*get_co_diam(char *str, t_co *co)
{
	int			j;
	char		*tmp;
	char		*tmp2;

	str = truncate_str(str);
	j = calc_i_double(str);
	tmp = ft_strsub(str, 0, j);
	co->rad = ft_atof(tmp) / 2;
	free(tmp);
	str = &(*(str + j));
	str = truncate_str(str);
	j = calc_i_double(str);
	tmp2 = ft_strsub(str, 0, j);
	co->height = ft_atof(tmp2);
	free(tmp2);
	str = &(*(str + j));
	str = truncate_str(str);
	j = calc_i_double(str);
	tmp2 = ft_strsub(str, 0, j);
	co->angl = ft_atof(tmp2);
	free(tmp2);
	str = &(*(str + j));
	return (str);
}

char
	*get_cones_data2(char *str, t_co *co)
{
	int			color[3];
	int			j;
	char		*tmp;

	str = get_co_diam(str, co);
	if (str == NULL)
		return (0);
	str = get_color(str, color);
	if (str == NULL)
		return (0);
	double_to_rgb(&co->mat.diffuse, color);
	str = truncate_str(str);
	j = calc_i_double(str);
	if (str && *str)
	{
		tmp = ft_strsub(str, 0, j);
		co->mat.reflection = ft_atof(tmp);
		free(tmp);
		str = &(*(str + j));
	}
	if (str && *str)
		co->mat.type = ft_atof(str);
	return (str);
}

int
	get_cones_data(char *str, void **ptr, t_stuff *st)
{
	int			res;
	t_co		*co;
	double		coor[3];
	static int	i;

	if (!(co = malloc(sizeof(t_co))))
		return (-1);
	ft_bzero(co, sizeof(t_co));
	res = 1;
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &co->pos);
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &co->dir);
	str = get_cones_data2(str, co);
	st->co_count = ++i;
	*ptr = co;
	return (res);
}

int
	check_cones_data(char *str, void **ptr, t_stuff *st)
{
	int res;

	res = 1;
	str += 2;
	str = truncate_str(str);
	if (!ft_strchr("0123456789-.", *str))
		res *= error_message("Cones contains invalide data.", st);
	if (get_cones_data(str, ptr, st) != 1)
		res *= error_message("Cones contains wrong point(s) or color(s).", st);
	return (res);
}
