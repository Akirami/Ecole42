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
	*get_sp_diam(char *str, t_sp *sp)
{
	int			j;
	char		*tmp;

	str = truncate_str(str);
	j = calc_i_double(str);
	tmp = ft_strsub(str, 0, j);
	sp->radius = ft_atof(tmp) / 2;
	free(tmp);
	str = &(*(str + j));
	str = truncate_str(str);
	return (str);
}

int
	get_sp_bonus(t_stuff *st, t_sp *sp, char *str)
{
	int		res;
	int		j;
	char	*tmp;

	res = 1;
	if (str && *str)
	{
		str = truncate_str(str);
		j = calc_i_double(str);
		tmp = ft_strsub(str, 0, j);
		sp->mat.reflection = ft_atof(tmp);
		free(tmp);
		str = &(*(str + j));
	}
	if (str && *str)
		sp->mat.type = ft_atof(str);
	if (sp->mat.type > TEXTURES + 10)
		res *= error_message("Textures ID out of range (sp).", st);
	return (res);
}

int
	get_spheres_data(char *str, void **ptr, t_stuff *st)
{
	int			res;
	t_sp		*sp;
	double		coor[3];
	int			color[3];
	static int	i;

	if (!(sp = malloc(sizeof(t_sp))))
		return (-1);
	ft_bzero(sp, sizeof(t_sp));
	res = 1;
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &sp->pos);
	str = get_sp_diam(str, sp);
	if (str == NULL)
		return (0);
	str = get_color(str, color);
	if (str == NULL)
		return (0);
	double_to_rgb(&sp->mat.diffuse, color);
	get_sp_bonus(st, sp, str);
	st->sp_count = ++i;
	*ptr = sp;
	return (res);
}

int
	check_spheres_data(char *str, void **ptr, t_stuff *st)
{
	int res;

	res = 1;
	str += 2;
	str = truncate_str(str);
	if (!ft_strchr("0123456789-.", *str))
		res *= error_message("Sphere contains invalide data.", st);
	if (get_spheres_data(str, ptr, st) != 1)
		res *= error_message("Sphere contains wrong point(s) or color(s).", st);
	return (res);
}
