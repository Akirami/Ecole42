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

void
	draw_hud3(t_stuff *st)
{
	mlx_string_put(st->context, st->window.win, 60, 265, 0x00adadef,
		ft_strjoin(" Spheres                      ", ft_itoa(st->sp_count)));
	mlx_string_put(st->context, st->window.win, 60, 280, 0x00adadef,
		ft_strjoin(" Planes                       ", ft_itoa(st->pl_count)));
	mlx_string_put(st->context, st->window.win, 60, 295, 0x00adadef,
		ft_strjoin(" Squares                      ", ft_itoa(st->sq_count)));
	mlx_string_put(st->context, st->window.win, 60, 310, 0x00adadef,
		ft_strjoin(" Triangles                    ", ft_itoa(st->tr_count)));
	mlx_string_put(st->context, st->window.win, 60, 325, 0x00adadef,
		ft_strjoin(" Cylenders                    ", ft_itoa(st->cy_count)));
	mlx_string_put(st->context, st->window.win, 60, 340, 0x00adadef,
		" Un autre truc                   ");
	mlx_string_put(st->context, st->window.win, 60, 355, 0x00adadef,
		" Peut etre meme deux             ");
	mlx_string_put(st->context, st->window.win, 60, 370, 0x00adadef,
		" Ou trois, on va pas charrier    ");
	mlx_string_put(st->context, st->window.win, 60, 390, 0x00adadef,
		"       == ELAPSED TIME ==        ");
	mlx_string_put(st->context, st->window.win, 60, 405, 0x00adadef,
		ft_strjoin(" From launch (ms)           ", ft_itoa(st->millis)));
	mlx_string_put(st->context, st->window.win, 60, 435, 0x00adadef,
		"      Press Space Bar to hide.   ");
}

void
	draw_hud2(t_stuff *st)
{
	mlx_string_put(st->context, st->window.win, 60, 75, 0x00adadef,
		"            == KEYS ==           ");
	mlx_string_put(st->context, st->window.win, 60, 95, 0x00adadef,
		" ESC:                Close MiniRT");
	mlx_string_put(st->context, st->window.win, 60, 120, 0x00adadef,
		" Q  :           Move Camera  Left");
	mlx_string_put(st->context, st->window.win, 60, 135, 0x00adadef,
		" D  :           Move Camera Right");
	mlx_string_put(st->context, st->window.win, 60, 150, 0x00adadef,
		" Z  :           Move Camera    Up");
	mlx_string_put(st->context, st->window.win, 60, 165, 0x00adadef,
		" S  :           Move Camera  down");
	mlx_string_put(st->context, st->window.win, 60, 180, 0x00adadef,
		" A  :         Rotate Camera  Left");
	mlx_string_put(st->context, st->window.win, 60, 195, 0x00adadef,
		" A  :         Rotate Camera Right");
	mlx_string_put(st->context, st->window.win, 60, 215, 0x00adadef,
		"            == INFO ==           ");
	mlx_string_put(st->context, st->window.win, 60, 235, 0x00adadef,
		ft_strjoin(" Cameras                      ", ft_itoa(st->cam_count)));
	mlx_string_put(st->context, st->window.win, 60, 250, 0x00adadef,
		ft_strjoin(" Lights                       ", ft_itoa(st->li_count)));
	draw_hud3(st);
}

int
	draw_hud(t_stuff *st)
{
	int x;
	int y;

	y = 50;
	while (++y < 450)
	{
		x = 50;
		while (++x < 305)
		{
			if ((y == 53 || y == 447) && (x > 55 && x < 300))
				mlx_pixel_put(st->context, st->window.win, x, y, 0x00c0c0c0);
			else if ((y == 54 || y == 446) && (x > 55 && x < 300))
				mlx_pixel_put(st->context, st->window.win, x, y, 0x00dd985c);
			else
				mlx_pixel_put(st->context, st->window.win, x, y, 0x0f000000);
		}
	}
	draw_hud2(st);
	return (1);
}
