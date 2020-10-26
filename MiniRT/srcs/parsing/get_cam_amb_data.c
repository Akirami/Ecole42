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
	get_window_size(char *str, t_stuff *stuff)
{
	int		i;
	char	*tmp;

	i = 0;
	str++;
	str = truncate_str(str);
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	tmp = ft_strsub(str, 0, i);
	if (!(*tmp))
		error_message("Wrong window size.", stuff);
	stuff->window.width = ft_atoi(tmp);
	free(tmp);
	str = &(*(str + i));
	stuff->window.height = ft_atoi(str);
	if (stuff->window.width < 1 || stuff->window.height < 1)
		error_message("Wrong window size.", stuff);
	if (stuff->window.width > RES_X)
		stuff->window.width = RES_X;
	if (stuff->window.height > RES_Y)
		stuff->window.height = RES_Y;
	return (1);
}

int
	get_ambient_light(char *str, t_stuff *st)
{
	int		i;
	char	*tmp;
	int		res;
	int		color[3];

	res = 1;
	str++;
	str = truncate_str(str);
	i = calc_i_double(str);
	tmp = ft_strsub(str, 0, i);
	st->amb.diff = ft_atof(tmp);
	if (st->amb.diff < 0 || st->amb.diff > 1)
		res *= error_message("Ambient light out of range.", st);
	free(tmp);
	str = &(*(str + i));
	str = get_color(str, color);
	if (str == NULL)
		res *= error_message("Wrong ambient light color.", st);
	double_to_rgb(&st->amb.color, color);
	st->amb.color.r *= st->amb.diff;
	st->amb.color.g *= st->amb.diff;
	st->amb.color.b *= st->amb.diff;
	return (res);
}

int
	get_cam_data(char *str, t_stuff *st)
{
	int			res;
	static int	i;
	double		coor[3];

	res = 1;
	str++;
	str = truncate_str(str);
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &st->obj.cam[i].pos);
	str = get_point(str, coor);
	if (str == NULL)
		return (0);
	double_to_vec(coor, &st->obj.cam[i].look_at);
	if (!check_dir(st->obj.cam[i].look_at))
		error_message("Invalid camera direction.", st);
	st->obj.cam[i].fov = ft_atof(str);
	if (st->obj.cam[i].fov < 0 || st->obj.cam[i].fov > 180)
		res *= error_message("FOV out of range.", st);
	st->obj.cam[i].fov = deg2rad(st->obj.cam[i].fov);
	st->obj.cam[i].isdraw = 0;
	st->cam_count = ++i;
	return (res);
}
