/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:24:48 by ikotvits          #+#    #+#             */
/*   Updated: 2018/08/25 10:24:49 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
int			get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

double		percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int			line_color(t_dot f, t_dot s, t_fdf *fdf)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	double			k;
	double percentage;

	if (fdf->draw->dx > fdf->draw->dy)
		percentage = percent(f.x * fdf->zoom + fdf->x_shift,
		fdf->draw->x2, fdf->draw->x1);
	else
		percentage = percent(f.y * fdf->zoom + fdf->y_shift,
		fdf->draw->y2, fdf->draw->y1);
	red = get_light((f.color >> 16) & 0xFF, (s.color >> 16) & 0xFF, percentage);
	green = get_light((f.color >> 8) & 0xFF, (s.color >> 8) & 0xFF, percentage);
	blue = get_light(f.color & 0xFF, s.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void		draw_line(t_dot first, t_dot second, t_fdf *fdf)
{
	fdf->draw->x1 = (int)(first.x * fdf->zoom + fdf->x_shift);
	fdf->draw->y1 = (int)(first.y * fdf->zoom + fdf->y_shift);
	fdf->draw->x2 = (int)(second.x * fdf->zoom + fdf->x_shift);
	fdf->draw->y2 = (int)(second.y * fdf->zoom + fdf->y_shift);
	fdf->draw->dx = ABS((fdf->draw->x2 - fdf->draw->x1));
	fdf->draw->dy = ABS((fdf->draw->y2 - fdf->draw->y1));
	fdf->draw->err = (fdf->draw->dx > fdf->draw->dy ?
	fdf->draw->dx : -(fdf->draw->dy)) / 2;
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

void		error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

void		init_ptr(t_fdf *fdf)
{
	int		bits_per_pixel;
	int		endian;
	int		size_line;

	bits_per_pixel = 32;
	endian = 0;
	size_line = fdf->win_size;
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->win_size, fdf->win_size);
	fdf->img = (int *)mlx_get_data_addr(fdf->img_ptr,
	&bits_per_pixel, &size_line, &endian);
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
}

void		redraw(t_fdf *fdf)
{
	int i;
	int j;

	i = -1;
	while (++i < fdf->win_size)
	{
		j = -1;
		while (++j < fdf->win_size)
			fdf->img[i * fdf->win_size + j] = 0;
	}
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	get_image(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}

int			start(t_fdf *fdf)
{
	fdf->draw = (t_draw *)malloc(sizeof(t_draw));
	get_map(fdf);
	init_ptr(fdf);
	return (1);
}

void		make_map_orig(t_fdf *fdf)
{
	int i;
	int	j;

	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->col)
		{
			fdf->dots[i][j].x = fdf->orig->orig_dots[i][j].x;
			fdf->dots[i][j].y = fdf->orig->orig_dots[i][j].y;
			fdf->dots[i][j].z = fdf->orig->orig_dots[i][j].z;
			fdf->dots[i][j].color = fdf->orig->orig_dots[i][j].color;
		}
	}
	fdf->zoom = fdf->orig->orig_zoom;
	fdf->x_shift = fdf->orig->orig_x_shift;
	fdf->y_shift = fdf->orig->orig_y_shift;
}

static int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		system("leaks -q a.out");
		exit(0);
	}
	(keycode == 15 && fdf->map) ? make_map_orig(fdf) : 0;
	(keycode == 12 && fdf->map) ? x_rotate(fdf, 0.03) : 0;
	(keycode == 0 && fdf->map) ? x_rotate(fdf, -0.03) : 0;
	(keycode == 13 && fdf->map) ? y_rotate(fdf, 0.03) : 0;
	(keycode == 1 && fdf->map) ? y_rotate(fdf, -0.03) : 0;
	(keycode == 14 && fdf->map) ? z_rotate(fdf, 0.03) : 0;
	(keycode == 2 && fdf->map) ? z_rotate(fdf, -0.03) : 0;
	(keycode == 8 && fdf->map) ? change_color(fdf) : 0;
	(keycode == 123 && fdf->dots) ? fdf->x_shift -= 11 : 0;
	(keycode == 124 && fdf->map) ? fdf->x_shift += 11 : 0;
	(keycode == 126 && fdf->map) ? fdf->y_shift -= 11 : 0;
	(keycode == 125 && fdf->map) ? fdf->y_shift += 11 : 0;
	(keycode == 27 && fdf->map) ? fdf->zoom /= 1.1 : 0;
	(keycode == 24 && fdf->map) ? fdf->zoom *= 1.1 : 0;
	(keycode == 49 && !fdf->map) ? start(fdf) : 0;
	(fdf->map) ? redraw(fdf) : 0;
	return (0);
}

void		first_scr(t_fdf *fdf)
{
	int len;

	len = fdf->win_size / 2 - 300;
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len, 0xFF0000, "FFFFFFFFFFFFFFFFFFFFFFDDDDDDDDDDDDD      FFFFFFFFFFFFFFFFFFFFFF");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 15, 0xFF0000, "F::::::::::::::::::::FD::::::::::::DDD   F::::::::::::::::::::F");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 30, 0xFF0000, "F::::::::::::::::::::FD:::::::::::::::DD F::::::::::::::::::::F");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 45, 0xFF0000, "FF::::::FFFFFFFFF::::FDDD:::::DDDDD:::::DFF::::::FFFFFFFFF::::F");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 60, 0xFF0000, "  F:::::F       FFFFFF  D:::::D    D:::::D F:::::F       FFFFFF");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 75, 0xFF0000, "  F:::::F               D:::::D     D:::::DF:::::F             ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 90, 0xFF0000, "  F::::::FFFFFFFFFF     D:::::D     D:::::DF::::::FFFFFFFFFF   ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 105, 0xFF0000, "  F:::::::::::::::F     D:::::D     D:::::DF:::::::::::::::F   ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 120, 0xFF0000, "  F:::::::::::::::F     D:::::D     D:::::DF:::::::::::::::F   ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 135, 0xFF0000, "  F::::::FFFFFFFFFF     D:::::D     D:::::DF::::::FFFFFFFFFF   ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 150, 0xFF0000, "  F:::::F               D:::::D     D:::::DF:::::F             ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 165, 0xFF0000, "  F:::::F               D:::::D    D:::::D F:::::F             ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 180, 0xFF0000, "FF:::::::FF           DDD:::::DDDDD:::::DFF:::::::FF           ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 195, 0xFF0000, "F::::::::FF           D:::::::::::::::DD F::::::::FF           ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 205, 0xFF0000, "F::::::::FF           D::::::::::::DDD   F::::::::FF           ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 220, 0xFF0000, "FFFFFFFFFFF           DDDDDDDDDDDDD      FFFFFFFFFFF           ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, fdf->win_size / 2 - 75,
	fdf->win_size * 0.9, 0xFF0000, "Just push SPACE");
}

static int	exit_x(void)
{
	exit(0);
}

int			main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (argc != 2)
		error("Usage: ./fdf your_map");
	fdf->fd = open(argv[1], O_RDONLY);
	if (fdf->fd < 1)
		error("Directory or invalid file");
	fdf->win_size = 1200;
	fdf->map = NULL;
	fdf->dots = NULL;
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr,
	fdf->win_size, fdf->win_size, "FCKN' FDF");
	first_scr(fdf);
	mlx_hook(fdf->win_ptr, 2, 0, key_hook, fdf);
	mlx_hook(fdf->win_ptr, 17, 1L << 17, exit_x, 0);
	mlx_hook(fdf->win_ptr, 6, 1L << 13, mouse_move, fdf);
	mlx_hook(fdf->win_ptr, 4, 1L << 2, mouse_press, fdf);
	mlx_hook(fdf->win_ptr, 5, 1L << 3, mouse_release, fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
