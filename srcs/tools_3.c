/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:41:58 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 10:43:35 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	search_min_height(int **height, int total)
{
	int	min;
	int	i;

	i = 0;
	min = 0;
	while (i < total)
	{
		if (height[i][2] < min)
			min = height[i][2];
		i++;
	}
	return (min);
}

int	search_max_height(int **height, int total)
{
	int	max;
	int	i;

	i = 0;
	max = 0;
	while (i < total)
	{
		if (height[i][2] > max)
			max = height[i][2];
		i++;
	}
	return (max);
}
