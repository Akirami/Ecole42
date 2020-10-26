/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:41:48 by emassard          #+#    #+#             */
/*   Updated: 2020/02/27 11:41:53 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_inter (*g_func_ptr[6])(t_stuff *st, void *obj, t_inter *ti, ray *r) = {
	intersect_r_sp,
	intersect_r_pl,
	intersect_r_tr,
	intersect_r_sq,
	intersect_r_cy,
	intersect_r_co
};

int (*g_objs_ptr[6])(char *str, void **obj, t_stuff *st) = {
	check_spheres_data,
	check_planes_data,
	check_triangles_data,
	check_squares_data,
	check_cylenders_data,
	check_cones_data
};

int
	free_stuff(t_stuff *st)
{
	int		i;

	i = -1;
	while (st->obj_count && ++i < st->obj_count)
		free(st->objs[i].ptr);
	ft_putendl("Closing MiniRT.");
	return (1);
}

int
	error_message(char *str, t_stuff *st)
{
	(void)st;
	ft_putstr("Error: ");
	ft_putendl(str);
	free_stuff(st);
	exit(1);
	return (0);
}

int
	check_data(char **data, int i, char *save)
{
	t_stuff	*st;
	t_objs	objs[i];

	if (!(st = (t_stuff *)malloc(sizeof(t_stuff))))
		return (0);
	ft_bzero(st, sizeof(t_stuff));
	if (save != NULL && !ft_strcmp(save, "-save"))
		st->save = 1;
	else if (save != NULL)
		error_message("Invalide data.", st);
	st->is_hud = false;
	st->t_begin = clock();
	st->objs = objs;
	if (!checking_obj_data(data, st))
		error_message("Invalide data.", st);
	return (init_context(st));
}

int
	read_data_file(char *str, char *save)
{
	int		fd;
	int		res;
	char	*line;
	char	**data;
	int		i;

	if (!(data = (char **)malloc(1000 * sizeof(char *))))
		return (-1);
	i = 0;
	fd = (str == NULL) ? open("default.rt", O_RDONLY) : open(str, O_RDONLY);
	while ((res = get_next_line(fd, &line)) > 0)
	{
		data[i] = ft_strdup(line);
		free(line);
		i++;
	}
	if (res < 0)
	{
		ft_putstr("Unable to read this file.\n");
		return (0);
	}
	data[i] = 0;
	return (check_data(data, i, save));
}

int
	main(int ac, char **av)
{
	int ret;

	ret = 1;
	if (ac == 1)
		ret = read_data_file(NULL, 0);
	else if (ac == 2)
		ret = read_data_file(av[1], 0);
	else if (ac == 3)
		ret = read_data_file(av[1], av[2]);
	if (ret < 0)
		ft_putstr("Exit with Error");
	if (!ret)
	{
		ft_putendl("Closing MiniRT.");
		exit(0);
	}
	ft_putendl("Closing MiniRT.");
	return (0);
}
