/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadrid- <amadrid-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:39:02 by amadrid-          #+#    #+#             */
/*   Updated: 2021/09/07 11:37:17 by amadrid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	neg(const char *nptr, int k)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)nptr;
	while (str[i] != '\0')
	{
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '+')
				k = 1;
			else if (str[i] == '-')
				k = -1;
			j++;
		}
		else if (str[i] > 47 && str[i] < 58)
			break ;
		i++;
	}
	if (j > 1)
		return (0);
	else
		return (k);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		i;
	int		k;
	int		l;

	i = 0;
	k = 0;
	l = neg(nptr, k + 1);
	str = (char *)nptr;
	while (str[i] == 32 || str[i] == '\n' || str[i] == '\t' || str[i] == \
		'\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	while (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		k = (k * 10) + (str[i] - '0');
		i++;
	}
	return (l * k);
}

int	calc_digit(int a)
{
	int	j;

	j = 0;
	if (a == 0)
		return (j = 1);
	else if (a < 0)
		j++;
	while (a != 0)
	{
		a = a / 10;
		j++;
	}
	return (j);
}

int	ft_isdigit_hex(char c)
{
	char	*digits;
	int		i;

	i = 0;
	digits = "0123456789ABCDEF";
	while (i < 16)
	{
		if (digits[i] == ft_toupper(c))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_hex(const char *str)
{
	int				i;
	int				sign;
	unsigned long	num;

	num = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	i += 2;
	while (ft_isdigit_hex(str[i]) >= 0)
		num = num * 16 + ft_isdigit_hex(str[i++]);
	return ((int)(num * sign));
}
