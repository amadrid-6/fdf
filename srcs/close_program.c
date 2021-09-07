/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:17:10 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 16:12:08 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(t_win *win, int w)
{
	int	i;

	free(win->map->height);
	free(win->map->color);
	if (w != 1)
	{
		i = -1;
		while (++i < win->map->l * win->map->w)
			free(win->points[i]);
		free(win->points);
		mlx_destroy_window(win->mlx, win->win);
	}
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	exit(0);
}

int	ft_sterror(int errnum, t_win *win)
{
	if (errnum == 1)
		write(1, "Error: Wrong map\n", 17);
	else if (errnum == 2)
		write (1, "Error: Cant draw the map\n", 19);
	else if (errnum == 3)
		write(1, "Error: Wrong FD\n", 16);
	else if (errnum == 4)
		write(1, "Error: Rows must be equal\n", 26);
	return (ft_close(win, 1));
}

int	key_esc(int keycode, t_win *win)
{
	if (keycode == KEY_ESC)
		ft_close(win, 0);
	return (1);
}

int	close_window(t_win *win)
{
	return (ft_close(win, 0));
}
