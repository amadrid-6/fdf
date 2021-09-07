/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:26:37 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 16:17:22 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_points(t_win *win)
{
	int	i;
	int	j;

	i = 0;
	j = win->map->w - 2;
	while (i < win->map->w * win->map->l - 1)
	{
		draw_vect_2_points(win->points[i + 1], win->points[i], win, i);
		if (i < win->map->w * win->map->l - win->map->w)
			draw_vect_2_points(win->points[i + win->map->w], \
				win->points[i], win, i + win->map->w);
		if (i == j && i != win->map->w * win->map->l - 2)
		{
			draw_vect_2_points(win->points[i + 1], \
				win->points[i + win->map->w + 1], win, i + 1);
			i += 2;
			j += win->map->w;
		}
		else
			i++;
	}
}

t_ddh	*create_ddh(int *point1, int *point2)
{
	t_ddh	*ddh;

	ddh = (t_ddh *)malloc(sizeof(t_ddh));
	ddh->dx = point1[0] - point2[0];
	ddh->dy = (point1[1] - point1[2]) - (point2[1] - point2[2]);
	if (abs(ddh->dx) > abs(ddh->dy))
		ddh->steps = abs(ddh->dx);
	else
		ddh->steps = abs(ddh->dy);
	ddh->xinc = ddh->dx / (float)ddh->steps;
	ddh->yinc = ddh->dy / (float)ddh->steps;
	ddh->x0 = point2[0];
	ddh->y0 = point2[1] - point2[2];
	ddh->h1 = point1[2];
	ddh->h2 = point2[2];
	ddh->xfin = point1[0];
	ddh->yfin = point1[1] - point1[2];
	ddh->x = point2[0];
	ddh->y = point2[1] - point2[2];
	ddh->scolor = 0x009900CC;
	ddh->ecolor = 0x009900CC;
	return (ddh);
}

void	draw_vect_2_points(int *point1, int *point2, t_win *win, int j)
{
	t_ddh	*ddh;
	int		i;
	int		k;

	ddh = create_ddh(point1, point2);
	i = 0;
	while (i <= ddh->steps)
	{
		color_height(ddh, win);
		k = check_if_color(win->map->color, win->map->l * win->map->w - 1);
		if (k == 0)
			ddh->color = get_color(ddh);
		else
			ddh->color = win->map->color[j];
		my_mlx_pixel_put(win->axes, ddh->x, ddh->y, ddh->color);
		ddh->x += ddh->xinc;
		ddh->y += ddh->yinc;
		i++;
	}
	free(ddh);
}

t_image	*new_image(t_win *win, int width, int height)
{
	t_image		*img;

	img = (t_image *)malloc(sizeof(t_image));
	img->img = mlx_new_image(win->mlx, width, height);
	img->data = mlx_get_data_addr(img->img, &img->bpp, \
		&img->size_line, &img->endian);
	img->width = width;
	img->height = height;
	return (img);
}
