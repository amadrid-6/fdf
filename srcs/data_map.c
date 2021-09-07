/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:23:55 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 16:18:44 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calc_map(t_win *win, t_map *map)
{
	float	width;
	float	length;
	float	point;

	map->x = (map->w - 1) * map->w_squ;
	map->y = (map->l - 1) * map->l_squ;
	width = map->x * (sqrt(3) / 2);
	length = map->y * (sqrt(3) / 2);
	point = map->y * 1 / 2 + map->x * 1 / 2;
	while (width + length > 1680 || point > 1000)
	{
		map->w_squ -= 1;
		map->l_squ -= 1;
		if (map->w_squ == 0 || map->l_squ == 0)
			return (ft_sterror(2, win));
		map->x = (map->w - 1) * map->w_squ;
		map->y = (map->l - 1) * map->l_squ;
		width = map->x * (sqrt(3) / 2);
		length = map->y * (sqrt(3) / 2);
		point = map->y * 1 / 2 + map->x * 1 / 2;
	}
	map->cenx = ((1680 - width - length) / 2) + length;
	map->ceny = (1000 - point) / 2;
	return (1);
}

int	**points_map(t_map *map)
{
	int		**points;
	int		i;
	int		j;
	float	x;
	float	y;

	i = -1;
	points = (int **)malloc(sizeof(int *) * map->w * map->l);
	while (++i < map->w * map->l)
		points[i] = (int *)malloc(sizeof(int) * 3);
	j = -1;
	while (++j < map->l)
	{
		i = -1;
		x = map->cenx - (j * map->l_squ * (sqrt(3) / 2));
		y = map->ceny + (j * map->l_squ * 1 / 2);
		while (++i < map->w)
		{
			points[i + map->w * j][0] = x + (i * map->w_squ * (sqrt(3) / 2));
			points[i + map->w * j][1] = y + (i * map->w_squ * 1 / 2);
			points[i + map->w * j][2] = map->height[i + map->w * j];
		}
	}
	return (points);
}
