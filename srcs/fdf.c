/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:43:57 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 16:31:12 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void	draw_screen(t_win *win)
{
	t_image	*axes;

	axes = new_image(win, win->width, win->height);
	win->axes = axes;
	draw_points(win);
	mlx_put_image_to_window(win->mlx, win->win, win->axes->img, 0, 0);
	mlx_destroy_image(win->mlx, win->axes->img);
	free(win->axes);
}

void	init_program(t_win win, char *file_name)
{
	win.mlx = mlx_init();
	read_map(&win, win.map, file_name);
	calc_map(&win, win.map);
	win.points = points_map(win.map);
	win.max_alt = search_max_height(win.points, win.map->l * win.map->w - 1);
	win.min_alt = search_min_height(win.points, win.map->l * win.map->w - 1);
	win.win = mlx_new_window(win.mlx, win.width, win.height, "fdf");
	draw_screen(&win);
	mlx_key_hook(win.win, key_esc, &win);
	mlx_hook(win.win, 33, 1L << 17, close_window, &win);
	mlx_loop(win.mlx);
}

void	init_map(t_win win, char *file_name)
{
	t_map	map;

	map.height = (int *)malloc(sizeof(int) * 500000);
	map.color = (int *)malloc(sizeof(int) * 500000);
	map.x = 0;
	map.y = 0;
	map.w = 0;
	map.l = 0;
	map.cenx = 0;
	map.ceny = 0;
	map.l_squ = 30;
	map.w_squ = 30;
	win.map = &map;
	init_program(win, file_name);
}

void	init_win(char *file_name)
{
	t_win	win;

	win.mlx = NULL;
	win.win = NULL;
	win.width = 1680;
	win.height = 1050;
	win.map = NULL;
	win.axes = NULL;
	win.points = NULL;
	win.max_alt = 0;
	win.min_alt = 0;
	win.scolor = 0x009900CC;
	win.ecolor = 0x0099FFCC;
	init_map(win, file_name);
}

int	main(int argc, char **argv)
{
	if (argc == 2 && ft_strnstr(argv[1], ".fdf", 100))
		init_win(argv[1]);
	else
		write(1, "Error: wrong arguments\n", 23);
	return (1);
}
