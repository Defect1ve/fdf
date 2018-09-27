/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 12:03:46 by ikotvits          #+#    #+#             */
/*   Updated: 2018/09/26 12:03:48 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		get_color(t_dot *dot, char *str)
{
	int		color;
	int		i;
	int		len;
	char	*base1;
	char	*base2;

	color = 0;
	len = -1;
	base1 = ft_strdup("0123456789ABCDEF");
	base2 = ft_strdup("0123456789abcdef");
	(str[0] != '0' || str[1] != 'x') ? error("Invalid color") : 0;
	str += 2;
	while (str[++len])
	{
		i = -1;
		while (base1[++i])
			if (base1[i] == str[len] || base2[i] == str[len])
				color += ft_pow(16, ft_strlen(str) - 1 - len) * i;
	}
	dot->color = color;
	ft_strdel(&base1);
	ft_strdel(&base2);
}

void		save_orig_map(t_fdf *fdf)
{
	int i;
	int j;

	fdf->zoom = (fdf->col < fdf->rows) ? (fdf->win_size * 0.6)
	/ fdf->rows : (fdf->win_size * 0.6) / fdf->col;
	fdf->orig = (t_orig *)malloc(sizeof(t_orig));
	i = -1;
	fdf->orig->orig_dots = (t_dot **)malloc(sizeof(t_dot *) * fdf->rows);
	while (++i < fdf->rows)
	{
		j = -1;
		fdf->orig->orig_dots[i] = (t_dot *)malloc(sizeof(t_dot) * fdf->col);
		while (++j < fdf->col)
		{
			fdf->orig->orig_dots[i][j].x = fdf->dots[i][j].x;
			fdf->orig->orig_dots[i][j].y = fdf->dots[i][j].y;
			fdf->orig->orig_dots[i][j].z = fdf->dots[i][j].z;
			fdf->orig->orig_dots[i][j].color = fdf->dots[i][j].color;
		}
	}
	fdf->orig->orig_zoom = fdf->zoom;
	fdf->orig->orig_x_shift = fdf->x_shift;
	fdf->orig->orig_y_shift = fdf->y_shift;
}

void		save_map_help(t_fdf *fdf, int i, t_map *map)
{
	int		k;
	int		j;
	char	**mass;

	fdf->dots[i] = (t_dot *)malloc(sizeof(t_dot) * fdf->col);
	mass = ft_strsplit(map->str, ' ');
	j = -1;
	while (mass && mass[++j] && j < fdf->col)
	{
		fdf->dots[i][j].x = j - fdf->col / 2;
		fdf->dots[i][j].y = i - fdf->rows / 2;
		fdf->dots[i][j].z = ft_atoi(mass[j]);
		fdf->dots[i][j].color = 0xFFFFFF;
		if (ft_strchr(mass[j], ','))
			get_color(&(fdf->dots[i][j]), ft_strchr(mass[j], ',') + 1);
	}
	k = -1;
	while (++k < fdf->col)
		free(mass[k]);
	free(mass);
}

void		save_map(t_fdf *fdf)
{
	int		i;
	t_map	*map;

	map = fdf->map;
	fdf->col = map ? words(map->str, ' ') : 0;
	i = -1;
	fdf->dots = (t_dot **)malloc(sizeof(t_dot *) * fdf->rows);
	while (map && ++i < fdf->rows)
	{
		(fdf->col != 0 && fdf->col != words(map->str, ' ')) ?
		error("Invalid num of cols") : 0;
		save_map_help(fdf, i, map);
		map = map->next;
	}
	fdf->x_shift = fdf->win_size / 2;
	fdf->y_shift = fdf->win_size / 2;
	save_orig_map(fdf);
}

void		get_map(t_fdf *fdf)
{
	t_map	*map;
	char	*line;

	fdf->rows = 0;
	while (get_next_line(fdf->fd, &line))
	{
		if (!fdf->map)
		{
			fdf->map = (t_map *)malloc(sizeof(t_map));
			map = fdf->map;
		}
		else
		{
			map = fdf->map;
			while (map->next)
				map = map->next;
			map->next = (t_map *)malloc(sizeof(t_map));
			map = map->next;
		}
		map->next = NULL;
		map->str = line;
		line = NULL;
		fdf->rows++;
	}
	save_map(fdf);
}
