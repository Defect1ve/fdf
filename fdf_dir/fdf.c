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
void	draw_line(t_dot first, t_dot second, t_fdf *fdf)
{
	fdf->draw->x1 = (int)(first.x + fdf->x_shift);
	fdf->draw->y1 = (int)(first.y + fdf->y_shift);
	fdf->draw->x2 = (int)(second.x + fdf->x_shift);
	fdf->draw->y2 = (int)(second.y + fdf->y_shift);
	fdf->draw->dx = ABS((fdf->draw->x2 - fdf->draw->x1));
	fdf->draw->dy = ABS((fdf->draw->y2 - fdf->draw->y1));
	fdf->draw->err = (fdf->draw->dx > fdf->draw->dy ?
	fdf->draw->dx : -(fdf->draw->dy)) / 2;
	while (fdf->draw->x1 != fdf->draw->x2 || fdf->draw->y1 != fdf->draw->y2)
	{
		if (fdf->draw->y1 < fdf->win_size && fdf->draw->x1 < fdf->win_size && fdf->draw->x1 >= 0 && fdf->draw->y1 >= 0)
			fdf->img[fdf->draw->y1 * fdf->win_size + fdf->draw->x1] = 0xFFFFFF;
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

void	error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

void	get_color(t_dot dot, char *str, char *base)
{
	int		color;
	int		i;
	int		len;

	color = 0;
	len = 5;
	if (str[0] != '0' || *str != 'x')
		error("Invalid color");
	else
		str += 2;
	while (*str)
	{
		i = -1;
		while (base[++i])
			if (base[i] == *str)
				color += ft_pow(16, len) * i;
		len--;
		str++;
	}
	dot.color = color;
}

static int		words(char const *s, char c)
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

void	save_map(t_fdf	*fdf)
{
	int		i;
	int		j;
	t_map	*map;
	char	**mass;

	map = fdf->map;
	fdf->col = map ? words(map->str, ' ') : 0;
	i = 0;
	fdf->zoom = (fdf->col < fdf->rows) ? (fdf->win_size * 0.8) / fdf->rows : (fdf->win_size * 0.8) / fdf->col;
	fdf->dots = (t_dot **)malloc(sizeof(t_dot *) * fdf->rows);
	while (map && i < fdf->rows)
	{
		(fdf->col != 0 && fdf->col != words(map->str, ' ')) ? error("Invalid num of cols") : 0;
		fdf->dots[i] = (t_dot *)malloc(sizeof(t_dot) * fdf->col);
		mass = ft_strsplit(map->str, ' ');
		j = -1;
		while (mass && mass[++j] && j < fdf->col)
		{
			fdf->dots[i][j].x = j * fdf->zoom;
			fdf->dots[i][j].y = i * fdf->zoom;
			fdf->dots[i][j].z = ft_atoi(mass[j]) * fdf->zoom;
			fdf->dots[i][j].color = 0x820505;
			if (ft_strchr(map->str, ','))
				get_color(fdf->dots[i][j], ft_strchr(map->str, ','), "01234567890abcde");
		}
		i++;
		map = map->next;
		for (int k = 0; k < fdf->col; k++)
			free(mass[k]);
		free(mass);
	}
	fdf->x_shift = (fdf->win_size - fdf->zoom * (fdf->col - 1)) / 2;
	fdf->y_shift = (fdf->win_size - fdf->zoom * (fdf->rows - 1)) / 2;
}

void	get_map(t_fdf	*fdf)
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
		free(line);
	}
	save_map(fdf);
}

void  init_ptr(t_fdf *fdf)
{
	int		bits_per_pixel;
	int		endian;
	int		size_line;

	bits_per_pixel = 32;
	endian = 0;// was 1
	size_line = fdf->win_size;
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr,fdf->win_size, fdf->win_size);
	fdf->img = (int *)mlx_get_data_addr(fdf->img_ptr, &bits_per_pixel, &size_line, &endian);
}

void	get_image(t_fdf *fdf)
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

void	x_rotate(t_fdf *fdf, double rotate)
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
			fdf->dots[i][j].y = y * cos(rotate) + fdf->dots[i][j].z * sin(rotate);
			fdf->dots[i][j].z = -y * sin(rotate) + fdf->dots[i][j].z * cos(rotate);
		}
	}
}

void	y_rotate(t_fdf *fdf, double rotate)
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
			fdf->dots[i][j].x = x * cos(rotate) + fdf->dots[i][j].z * sin(rotate);
			fdf->dots[i][j].z = -x * sin(rotate) + fdf->dots[i][j].z * cos(rotate);
		}
	}
}

void	z_rotate(t_fdf *fdf, double rotate)
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

void	redraw(t_fdf *fdf)
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

int		start(t_fdf	*fdf)
{
	fdf->draw = (t_draw *)malloc(sizeof(t_draw));
	get_map(fdf);
	init_ptr(fdf);
	return(1);
}

static int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(0);
	}
	(keycode == 12 && fdf->map) ? x_rotate(fdf, 0.03) : 0;
	(keycode == 0 && fdf->map) ? x_rotate(fdf, -0.03) : 0;
	(keycode == 13 && fdf->map) ? y_rotate(fdf, 0.03) : 0;
	(keycode == 1 && fdf->map) ? y_rotate(fdf, -0.03) : 0;
	(keycode == 14 && fdf->map) ? z_rotate(fdf, 0.03) : 0;
	(keycode == 2 && fdf->map) ? z_rotate(fdf, -0.03) : 0;
	(keycode == 123 && fdf->dots) ? fdf->x_shift -= 11 : 0;
	(keycode == 124 && fdf->map) ? fdf->x_shift += 11 : 0;
	(keycode == 125 && fdf->map) ? fdf->y_shift += 11 : 0;
	(keycode == 126 && fdf->map) ? fdf->y_shift -= 11 : 0;
	(keycode == 49 && !fdf->map) ? start(fdf) : 0;
	(fdf->map) ? redraw(fdf) : 0;
	return (0);
}

void		first_scr(t_fdf	*fdf)
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

int		main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (argc != 2)
		error("Usage: ./fdf your_map");
	fdf->fd = open(argv[1], O_RDONLY);
	if (fdf->fd < 1)
		error("Invalid file");
	fdf->win_size = 1200;
	fdf->map = NULL;
	fdf->dots = NULL;
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr,
	fdf->win_size, fdf->win_size, "FCKN' FDF");
	first_scr(fdf);
	mlx_hook(fdf->win_ptr, 2, 0, key_hook, fdf);
	mlx_hook(fdf->win_ptr, 17, 1L << 17, exit_x, 0);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
