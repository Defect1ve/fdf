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
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0,
	0, 0x204c39, "ROTATE: Q/A, W/S, E/D (mouse)");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0,
	20, 0x204c39, "ZOOM: +/- (mouse)");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0,
	40, 0x204c39, "RESPAWN: R");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0,
	60, 0x204c39, "CHANGE COLOR: C");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0,
	80, 0x204c39, "MOVE: keyboard arrows");
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
	(keycode == 27 && fdf->map && fdf->zoom > 1) ? fdf->zoom /= 1.1 : 0;
	(keycode == 24 && fdf->map && fdf->zoom < 100) ? fdf->zoom *= 1.1 : 0;
	(fdf->map) ? redraw(fdf) : 0;
	return (0);
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
	fdf->win_size = 1300;
	fdf->map = NULL;
	fdf->dots = NULL;
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr,
	fdf->win_size, fdf->win_size, "FCKN' FDF");
	start(fdf);
	first_scr(fdf);
	mlx_hook(fdf->win_ptr, 2, 0, key_hook, fdf);
	mlx_hook(fdf->win_ptr, 17, 1L << 17, exit_x, 0);
	mlx_hook(fdf->win_ptr, 6, 1L << 13, mouse_move, fdf);
	mlx_hook(fdf->win_ptr, 4, 1L << 2, mouse_press, fdf);
	mlx_hook(fdf->win_ptr, 5, 1L << 3, mouse_release, fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
