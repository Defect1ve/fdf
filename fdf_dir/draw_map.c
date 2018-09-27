/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:36:39 by ikotvits          #+#    #+#             */
/*   Updated: 2018/09/27 14:36:43 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		rat(int start, int end, int current)
{
	return ((end == start) ? 1.0 :
	((double)(current - start) / (double)(end - start)));
}

int			line_color(t_dot f, t_dot s, t_fdf *fdf)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	double			ratio;

	if (fdf->draw->dx > fdf->draw->dy)
		ratio = rat(f.x * fdf->zoom + fdf->x_shift,
		fdf->draw->x2, fdf->draw->x1);
	else
		ratio = rat(f.y * fdf->zoom + fdf->y_shift,
		fdf->draw->y2, fdf->draw->y1);
	red = (double)((1 - ratio) * ((f.color >> 16) & 0xFF)
	+ ratio * ((s.color >> 16) & 0xFF));
	green = (double)((1 - ratio) * ((f.color >> 8) & 0xFF)
	+ ratio * ((s.color >> 8) & 0xFF));
	blue = (double)((1 - ratio) * (f.color & 0xFF) + ratio * (s.color & 0xFF));
	return ((red << 16) | (green << 8) | blue);
}

void		draw_line_prepare(t_fdf *fdf, t_dot f, t_dot s)
{
	fdf->draw->x1 = (int)(f.x * fdf->zoom + fdf->x_shift);
	fdf->draw->y1 = (int)(f.y * fdf->zoom + fdf->y_shift);
	fdf->draw->x2 = (int)(s.x * fdf->zoom + fdf->x_shift);
	fdf->draw->y2 = (int)(s.y * fdf->zoom + fdf->y_shift);
	fdf->draw->dx = ABS((fdf->draw->x2 - fdf->draw->x1));
	fdf->draw->dy = ABS((fdf->draw->y2 - fdf->draw->y1));
	fdf->draw->err = (fdf->draw->dx > fdf->draw->dy ?
	fdf->draw->dx : -(fdf->draw->dy)) / 2;
}

void		draw_line(t_dot first, t_dot second, t_fdf *fdf)
{
	draw_line_prepare(fdf, first, second);
	if (fdf->draw->y2 < fdf->win_size && fdf->draw->x2 <
	fdf->win_size && fdf->draw->x2 >= 0 && fdf->draw->y2 >= 0)
		fdf->img[fdf->draw->y2 * fdf->win_size + fdf->draw->x2] = second.color;
	while (fdf->draw->x1 != fdf->draw->x2 || fdf->draw->y1 != fdf->draw->y2)
	{
		if (fdf->draw->y1 < fdf->win_size && fdf->draw->x1 < fdf->win_size
		&& fdf->draw->x1 >= 0 && fdf->draw->y1 >= 0)
			fdf->img[fdf->draw->y1 * fdf->win_size +
			fdf->draw->x1] = line_color(first, second, fdf);
		fdf->draw->e2 = fdf->draw->err;
		if (fdf->draw->e2 > -(fdf->draw->dx))
		{
			fdf->draw->err -= fdf->draw->dy;
			fdf->draw->x1 += fdf->draw->x1 < fdf->draw->x2 ? 1 : -1;
		}
		if (fdf->draw->e2 < fdf->draw->dy)
		{
			fdf->draw->err += fdf->draw->dx;
			fdf->draw->y1 += fdf->draw->y1 < fdf->draw->y2 ? 1 : -1;
		}
	}
}

void		get_image(t_fdf *fdf)
{
	int i;
	int j;

	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->col)
		{
			if (i + 1 < fdf->rows)
				draw_line(fdf->dots[i][j], fdf->dots[i + 1][j], fdf);
			if (j + 1 < fdf->col)
				draw_line(fdf->dots[i][j], fdf->dots[i][j + 1], fdf);
		}
	}
	if (fdf->col == 1 && fdf->rows == 1)
		draw_line(fdf->dots[0][0], fdf->dots[0][0], fdf);
}
