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
	checking_other_data(char **str, t_stuff *st)
{
	int			i;
	int			res;

	res = 1;
	i = -1;
	while (str[++i] != 0)
	{
		if (str[i] && str[i][0] == '#')
			continue ;
		else if (str[i] && str[i][0] == 'R' &&
			ft_strchr("\t\v\n\f\r ", str[i][1]))
			res *= get_window_size(str[i], st);
		else if (str[i] && str[i][0] == 'A' &&
			ft_strchr("\t\v\n\f\r ", str[i][1]))
			res *= get_ambient_light(str[i], st);
		else if (str[i] && str[i][0] == 'c' &&
			ft_strchr("\t\v\n\f\r ", str[i][1]))
			res *= get_cam_data(str[i], st);
		else if (str[i] && str[i][0] == 'l' &&
			ft_strchr("\t\v\n\f\r ", str[i][1]))
			res *= check_light_data(str[i], st);
		if (res < 1)
			return (0);
	}
	return (res);
}

int
	checking_obj_data2(char *str, t_stuff *st, int i, int j)
{
	int		res;

	res = 1;
	res *= (*g_objs_ptr[i])(str, &st->objs[j].ptr, st);
	if (res == 0)
		error_message("Wrong data.\n", st);
	st->objs[j].type = i;
	j++;
	return (j);
}

int
	checking_obj_data3(char **str, t_stuff *st, int i, int j)
{
	if (str[i] && str[i][0] == 's' && str[i][1] == 'p')
		j = checking_obj_data2(str[i], st, 0, j);
	else if (str[i] && str[i][0] == 'p' && str[i][1] == 'l')
		j = checking_obj_data2(str[i], st, 1, j);
	else if (str[i] && str[i][0] == 't' && str[i][1] == 'r')
		j = checking_obj_data2(str[i], st, 2, j);
	else if (str[i] && str[i][0] == 's' && str[i][1] == 'q')
		j = checking_obj_data2(str[i], st, 3, j);
	else if (str[i] && str[i][0] == 'c' && str[i][1] == 'y')
		j = checking_obj_data2(str[i], st, 4, j);
	else if (str[i] && str[i][0] == 'c' && str[i][1] == 'o')
		j = checking_obj_data2(str[i], st, 5, j);
	else if (str[i] && str[i][0] == 'c' && str[i][1] == 'u')
		j = check_cubes_data(str[i], st, j);
	else if (str[i] && str[i][0] == 'p' && str[i][1] == 'y')
		j = check_pyra_data(str[i], st, j);
	return (j);
}

int
	checking_obj_data(char **str, t_stuff *st)
{
	int	i;
	int	j;
	int	res;

	res = 1;
	i = -1;
	j = 0;
	res *= checking_other_data(str, st);
	while (str[++i] != 0)
	{
		if (str[i] && str[i][0] == '#')
		{
			free(str[i]);
			continue ;
		}
		else
			j = checking_obj_data3(str, st, i, j);
		if (res < 1)
			return (0);
		st->obj_count = j;
		free(str[i]);
	}
	return (res);
}
