/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 12:20:09 by ikotvits          #+#    #+#             */
/*   Updated: 2018/09/26 12:20:10 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		x_rotate(t_fdf *fdf, double rotate)
{
	int		i;
	int		j;
	double	y;

	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->col)
		{
			y = fdf->dots[i][j].y;
			fdf->dots[i][j].y = y * cos(rotate) +
			fdf->dots[i][j].z * sin(rotate);
			fdf->dots[i][j].z = -y * sin(rotate) +
			fdf->dots[i][j].z * cos(rotate);
		}
	}
}

void		y_rotate(t_fdf *fdf, double rotate)
{
	int		i;
	int		j;
	double	x;

	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->col)
		{
			x = fdf->dots[i][j].x;
			fdf->dots[i][j].x = x * cos(rotate) +
			fdf->dots[i][j].z * sin(rotate);
			fdf->dots[i][j].z = -x * sin(rotate) +
			fdf->dots[i][j].z * cos(rotate);
		}
	}
}

void		z_rotate(t_fdf *fdf, double rotate)
{
	int		i;
	int		j;
	double	x;
	double	y;

	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->col)
		{
			x = fdf->dots[i][j].x;
			y = fdf->dots[i][j].y;
			fdf->dots[i][j].x = x * cos(rotate) - y * sin(rotate);
			fdf->dots[i][j].y = x * sin(rotate) + y * cos(rotate);
		}
	}
}

void		change_color(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->col)
			fdf->dots[i][j].color += 0x010110;
	}
}

int			words(char const *s, char c)
{
	int i;
	int t;
	int check;

	i = 0;
	t = 0;
	check = 0;
	while (s && s[t] != '\0')
	{
		if (s[t] == c && check)
			check = 0;
		else if (s[t] != c && !check)
		{
			check = 1;
			i++;
		}
		t++;
	}
	return (i);
}
