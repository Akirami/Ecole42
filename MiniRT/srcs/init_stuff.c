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

#include "../includes/minirt.h"

int
	hook_events(int x, int y, t_stuff *st)
{
	printf("EV: %d %d \n", x, y);
	close_minirt2(st);
	return (0);
}

int
	close_minirt2(t_stuff *stuff)
{
	(void)stuff;
	free_stuff(stuff);
	exit(0);
	return (0);
}

int
	close_minirt(t_stuff *stuff)
{
	mlx_clear_window(stuff->context, stuff->window.win);
	mlx_destroy_window(stuff->context, stuff->window.win);
	free_stuff(stuff);
	exit(0);
	return (0);
}

int
	get_window(t_stuff *stuff)
{
	if (!(stuff->window.win = (void *)malloc(stuff->window.width
		* stuff->window.height * sizeof(void))))
		return (0);
	if (!((stuff->window.win = mlx_new_window(stuff->context,
		stuff->window.width, stuff->window.height, "MiniRT"))))
	{
		ft_putstr("Error new window !!");
		return (-1);
	}
	return (main_loop(stuff));
}

int
	init_context(t_stuff *stuff)
{
	if (!(stuff->context = mlx_init()))
	{
		ft_putstr("Error init mlx !!");
		return (-1);
	}
	return (get_window(stuff));
}
