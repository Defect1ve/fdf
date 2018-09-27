/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_trash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:41:29 by ikotvits          #+#    #+#             */
/*   Updated: 2018/09/27 14:41:30 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			exit_x(void)
{
	exit(0);
}

void		error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

int			start(t_fdf *fdf)
{
	fdf->draw = (t_draw *)malloc(sizeof(t_draw));
	get_map(fdf);
	init_ptr(fdf);
	return (1);
}

void		first_scr2(t_fdf *fdf, int len)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 135, 0xFF0000,
	"  F::::::FFFFFFFFFF     D:::::D     D:::::DF::::::FFFFFFFFFF   ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 150, 0xFF0000,
	"  F:::::F               D:::::D     D:::::DF:::::F             ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 165, 0xFF0000,
	"  F:::::F               D:::::D    D:::::D F:::::F             ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 180, 0xFF0000,
	"FF:::::::FF           DDD:::::DDDDD:::::DFF:::::::FF           ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 195, 0xFF0000,
	"F::::::::FF           D:::::::::::::::DD F::::::::FF           ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 205, 0xFF0000,
	"F::::::::FF           D::::::::::::DDD   F::::::::FF           ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 220, 0xFF0000,
	"FFFFFFFFFFF           DDDDDDDDDDDDD      FFFFFFFFFFF           ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, fdf->win_size / 2 - 75,
	fdf->win_size * 0.9, 0xFF0000, "Just push SPACE");
}

void		first_scr(t_fdf *fdf)
{
	int len;

	len = fdf->win_size / 2 - 300;
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len, 0xFF0000,
	"FFFFFFFFFFFFFFFFFFFFFFDDDDDDDDDDDDD      FFFFFFFFFFFFFFFFFFFFFF");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 15, 0xFF0000,
	"F::::::::::::::::::::FD::::::::::::DDD   F::::::::::::::::::::F");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 30, 0xFF0000,
	"F::::::::::::::::::::FD:::::::::::::::DD F::::::::::::::::::::F");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 45, 0xFF0000,
	"FF::::::FFFFFFFFF::::FDDD:::::DDDDD:::::DFF::::::FFFFFFFFF::::F");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 60, 0xFF0000,
	"  F:::::F       FFFFFF  D:::::D    D:::::D F:::::F       FFFFFF");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 75, 0xFF0000,
	"  F:::::F               D:::::D     D:::::DF:::::F             ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 90, 0xFF0000,
	"  F::::::FFFFFFFFFF     D:::::D     D:::::DF::::::FFFFFFFFFF   ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 105, 0xFF0000,
	"  F:::::::::::::::F     D:::::D     D:::::DF:::::::::::::::F   ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, len, len + 120, 0xFF0000,
	"  F:::::::::::::::F     D:::::D     D:::::DF:::::::::::::::F   ");
	first_scr2(fdf, len);
}