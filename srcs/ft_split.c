/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 14:01:59 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 10:32:34 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	numstr(char const *str, char c)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == c)
	{
		i++;
		if (str[i] == '\0')
			return (0);
	}
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			j++;
		i++;
	}
	return (j + 1);
}

static	int	ft_strlenc(char const *str, char c, int i)
{
	unsigned int	l;

	l = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		l++;
		i++;
	}
	return (l);
}

static	char	**clean(char const **dest, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)dest[j]);
	}
	free(dest);
	return (NULL);
}

static	char	**fill(char const *s, char **dest, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		dest[j] = (char *)malloc(sizeof(char ) * ft_strlenc(s, c, i) + 1);
		if (dest == NULL)
			return (clean((char const **)dest, j));
		while (s[i] != '\0' && s[i] != c)
		{
			dest[j][k] = s[i];
			k++;
			i++;
		}
		dest[j][k] = '\0';
		j++;
	}
	dest[j] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char		**dest;
	int			i;

	i = numstr(s, c);
	dest = (char **)malloc(sizeof(char *) * (i + 1));
	if (dest == NULL)
		return (NULL);
	dest = fill(s, dest, c, i);
	return (dest);
}
