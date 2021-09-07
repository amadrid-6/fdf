/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:42:58 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 11:42:59 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
		c == '\r' || c == ' ');
}

int	ft_toupper(int c)
{
	if (c < -1)
		return (c + 256);
	if (c > 96 && c < 123)
		c -= 32;
	return (c);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	size_t	needle_len;
	size_t	haystack_len;
	size_t	i;
	size_t	j;

	h = (char *)haystack;
	haystack_len = ft_strlen((char *)haystack);
	needle_len = ft_strlen((char *)needle);
	if (!needle_len)
		return (h);
	if (haystack_len < needle_len || len < needle_len)
		return (NULL);
	i = 0;
	while (h[i] && i <= len - needle_len)
	{
		j = 0;
		while (needle[j] && needle[j] == h[i + j])
			j++;
		if (j == needle_len)
			return (&h[i]);
		i++;
	}
	return (NULL);
}

void	free_2d(void **arg)
{
	int	i;

	if (arg != NULL)
	{
		i = -1;
		while (arg[++i])
			free(arg[i]);
		free(arg);
		arg = NULL;
	}
}

int	check_if_color(int *color, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (color[i] != 16777215 && color[i] != 0)
			return (1);
		i++;
	}
	return (0);
}
