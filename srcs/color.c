/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:18:58 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 16:14:58 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	percent(int start, int end, int current)
{
	double	place;
	double	distance;

	place = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	else
		return (place / distance);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(t_ddh *ddh)
{
	int		r;
	int		g;
	int		b;
	double	percentage;

	if (ddh->dx > ddh->dy)
		percentage = percent(ddh->x0, ddh->xfin, ddh->x);
	else
		percentage = percent(ddh->y0, ddh->yfin, ddh->y);
	r = get_light((ddh->scolor >> 16) & 0xFF, \
		(ddh->ecolor >> 16) & 0xFF, percentage);
	g = get_light((ddh->scolor >> 8) & 0xFF, \
		(ddh->ecolor >> 8) & 0xFF, percentage);
	b = get_light(ddh->scolor & 0xFF, \
		ddh->ecolor & 0xFF, percentage);
	return (r << 16 | g << 8 | b);
}

int	rgb(t_win *win, double percent)
{
	int	r;
	int	g;
	int	b;

	r = get_light((win->scolor >> 16) & 0xFF, \
		(win->ecolor >> 16) & 0xFF, percent);
	g = get_light((win->scolor >> 8) & 0xFF, \
		(win->ecolor >> 8) & 0xFF, percent);
	b = get_light(win->scolor & 0xFF, win->ecolor & 0xFF, percent);
	return (r << 16 | g << 8 | b);
}

void	color_height(t_ddh *ddh, t_win *win)
{
	int		scolor;
	int		ecolor;
	float	percent1;
	float	percent2;

	if (win->max_alt > 0)
	{
		percent1 = (float)ddh->h2 / (float)win->max_alt;
		ecolor = rgb(win, percent1);
		percent2 = (float)ddh->h1 / (float)win->max_alt;
		scolor = rgb(win, percent2);
		ddh->scolor = ecolor;
		ddh->ecolor = scolor;
	}
	else if (win->max_alt == 0 && win->min_alt < 0)
	{
		percent1 = (float)ddh->h2 / fabs((float)(win->min_alt));
		scolor = rgb(win, percent1);
		percent2 = (float)ddh->h1 / fabs((float)(win->min_alt));
		ecolor = rgb(win, percent2);
		ddh->scolor = ecolor;
		ddh->ecolor = scolor;
	}
}
