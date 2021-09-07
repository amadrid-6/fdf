/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:13:08 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 16:22:46 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include <stdio.h>

# define KEY_ESC	0xff1b

typedef struct s_image
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		size_line;
	int		bpp;
	int		endian;
}		t_image;

typedef struct s_map
{
	int	x;
	int	y;
	int	w;
	int	l;
	int	l_squ;
	int	w_squ;
	int	cenx;
	int	ceny;
	int	*height;
	int	*color;
}		t_map;

typedef struct s_ddh
{
	unsigned int	color;
	int				scolor;
	int				ecolor;
	int				dx;
	int				dy;
	int				steps;
	int				x0;
	int				y0;
	int				h1;
	int				h2;
	int				xfin;
	int				yfin;
	float			xinc;
	float			yinc;
	float			x;
	float			y;
}		t_ddh;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int		max_alt;
	int		min_alt;
	int		scolor;
	int		ecolor;
	int		gate;
	int		**points;
	t_map	*map;
	t_image	*axes;
}		t_win;

void	draw_ver_line(t_win *win, t_image *axes);
void	draw_plane(t_win *win, t_image *axes);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	draw_points(t_win *win);
void	draw_vect_2_points(int *point1, int *point2, t_win *win, int j);
void	draw_axes(t_win *win, t_image *axes);
t_image	*new_image(t_win *win, int width, int height);
t_ddh	*create_ddh(int *point1, int *point2);

int		calc_map(t_win *win, t_map *map);
int		**points_map(t_map *map);
int		check_color(int x, int y, int i, t_image *axes);
int		color_white(int x, int y, t_image *axes);
int		parse_map(char *line, int l, t_map *map);
void	read_map(t_win *win, t_map *map, char *line);
int		check_map(char **num);
int		check_hex(char *line, int j);
int		return_check(char **num, int j);

int		check_intersect(int i, t_win *win, t_image *axes);
int		neg(const char *nptr, int k);
int		ft_atoi(const char *nptr);
int		calc_digit(int a);
int		search_max_height(int **height, int total);
int		search_min_height(int **height, int total);

double	percent(int start, int end, int current);
int		get_light(int start, int end, double percentage);
int		get_color(t_ddh *ddh);
int		rgb(t_win *win, double percent);
void	color_height(t_ddh *ddh, t_win *win);

int		ft_isdigit_hex(char c);
int		ft_atoi_hex(const char *str);
int		ft_isspace(int c);
int		ft_toupper(int c);
int		check_if_color(int *color, int total);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	free_2d(void **arg);

void	draw_screen(t_win *win);
void	init_program(t_win win, char *file_name);
void	init_map(t_win win, char *file_name);
void	init_win(char *file_name);

int		key_esc(int keycode, t_win *win);
int		close_window(t_win *win);
int		ft_close(t_win *win, int w);
int		ft_sterror(int errnum, t_win *win);

char	**ft_split(const char *s, char c);
#endif
