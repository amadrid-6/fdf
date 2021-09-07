/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:25:02 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 16:36:46 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

int	check_hex(char *line, int j)
{
	int	k;

	k = 0;
	if (line[j] == '0' && line[j + 1] == 'x')
		j += 2;
	else
		return (-1);
	while (line[j] != '\0')
	{
		k = ft_isdigit_hex(line[j]);
		if (k == -1)
			return (-1);
		j++;
	}
	return (j);
}

int	check_map(char **num)
{
	int		i;
	size_t	j;

	i = 0;
	while (num[i] != NULL)
	{
		j = 0;
		if (num[i][j] == '-')
			j++;
		if (num[i][j] >= '0' && num[i][j] <= '9')
		{
			while (num[i][j] >= '0' && num[i][j] <= '9')
				j++;
		}
		if (num[i][j] == ',')
			j = check_hex(num[i], j + 1);
		if (j == ft_strlen(num[i]))
			i++;
		else
			return (-1);
	}
	return (0);
}

int	return_check(char **num, int j)
{
	if (check_map(num) != -1)
	{
		free_2d((void **)num);
		return (j);
	}
	else
	{
		free_2d((void **)num);
		return (0);
	}
}

int	parse_map(char *line, int l, t_map *map)
{
	int		i;
	int		j;
	int		k;
	char	**num;

	num = ft_split(line, ' ');
	i = 0;
	j = 0;
	while (num[i] != NULL)
	{
		k = 0;
		map->height[l * map->w + j] = ft_atoi(num[i]);
		k += calc_digit(map->height[l * map->w + j]);
		if (num[i][k] == ',')
			map->color[l * map->w + j] = ft_atoi_hex(&num[i][k + 1]);
		else
			map->color[l * map->w + j] = ft_atoi_hex("0xFFFFFF");
		j++;
		i++;
	}
	return (return_check(num, j));
}

void	read_map(t_win *win, t_map *map, char *file_name)
{
	int		fd;
	int		w;
	int		l;
	int		j;
	char	*line;

	l = 0;
	j = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_sterror(3, win);
	while (get_next_line(fd, &line))
	{
		w = parse_map(line, l, map);
		free(line);
		if (l > 0 && (map->w != w || w == 0))
			j = -1;
		map->w = w;
		l++;
	}
	free(line);
	map->l = l;
	close(fd);
	if (j == -1)
		ft_sterror(1, win);
}
