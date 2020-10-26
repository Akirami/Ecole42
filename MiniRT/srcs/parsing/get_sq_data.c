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
	check_planes_data2(char *str, t_pl *pl, t_stuff *st)
{
	int		res;
	int		color[3];
	int		j;
	char	*tmp;

	res = 1;
	str = get_color(str, color);
	if (str == NULL)
		res *= error_message("Wrong plan color.", st);
	double_to_rgb(&pl->mat.diffuse, color);
	str = truncate_str(str);
	j = calc_i_double(str);
	if (str && *str)
	{
		tmp = ft_strsub(str, 0, j);
		pl->mat.reflection = ft_atof(tmp);
		free(tmp);
		str = &(*(str + j));
	}
	if (str && *str)
		pl->mat.type = ft_atof(str);
	if (pl->mat.type > 1)
		res *= error_message("Plan texture type out of range.", st);
	return (res);
}

int
	check_planes_data(char *str, void **ptr, t_stuff *st)
{
	int			res;
	static int	i;
	double		coor[3];
	t_pl		*pl;

	if (!(pl = malloc(sizeof(t_pl))))
		return (-1);
	ft_bzero(pl, sizeof(t_pl));
	res = 1;
	str += 2;
	str = truncate_str(str);
	str = get_point(str, coor);
	if (str == NULL)
		res *= error_message("Wrong plan point.", st);
	double_to_vec(coor, &pl->pos);
	str = get_point(str, coor);
	if (str == NULL)
		res *= error_message("Wrong plan point.", st);
	double_to_vec(coor, &pl->norm);
	if (!check_dir(pl->norm))
		error_message("Invalid normal plan.", st);
	res *= check_planes_data2(str, pl, st);
	st->pl_count = ++i;
	*ptr = pl;
	return (res);
}

char
	*check_squares_data3(t_stuff *st, char *str, t_sq *sq)
{
	int		j;
	char	*tmp;

	j = 0;
	str = truncate_str(str);
	j = calc_i_double(str);
	if (str && *str)
	{
		tmp = ft_strsub(str, 0, j);
		sq->mat.reflection = ft_atof(tmp);
		free(tmp);
		str = &(*(str + j));
	}
	else
		sq->mat.reflection = 0;
	if (str && *str)
		sq->mat.type = ft_atof(str);
	if (sq->mat.type > TEXTURES + 10)
		error_message("Textures ID out of range (sq).", st);
	return (str);
}

char
	*check_squares_data2(char *str, t_sq *sq, t_stuff *st)
{
	int			res;
	int			j;
	char		*tmp;
	int			color[3];

	if (!check_dir(sq->norm))
		error_message("Invalid normal square.", st);
	res = 1;
	str = truncate_str(str);
	j = calc_i_double(str);
	tmp = ft_strsub(str, 0, j);
	sq->len = ft_atof(tmp);
	if (sq->len <= 0)
		res *= error_message("Wrong square lenght.", st);
	free(tmp);
	str = &(*(str + j));
	str = get_color(str, color);
	if (str == NULL)
		res *= error_message("Wrong square color.", st);
	double_to_rgb(&sq->mat.diffuse, color);
	str = truncate_str(str);
	if (str && *str)
		str = check_squares_data3(st, str, sq);
	return (str);
}

int
	check_squares_data(char *str, void **ptr, t_stuff *st)
{
	int			res;
	static int	i;
	double		coor[3];
	t_sq		*sq;

	if (!(sq = malloc(sizeof(t_sq))))
		return (-1);
	ft_bzero(sq, sizeof(t_sq));
	str += 2;
	res = 1;
	str = truncate_str(str);
	str = get_point(str, coor);
	if (str == NULL)
		res *= error_message("Wrong square point.", st);
	double_to_vec(coor, &sq->pos);
	str = get_point(str, coor);
	if (str == NULL)
		res *= error_message("Wrong square normales.", st);
	double_to_vec(coor, &sq->norm);
	str = check_squares_data2(str, sq, st);
	st->sq_count = ++i;
	*ptr = sq;
	prepare_sq(sq);
	return (res);
}
