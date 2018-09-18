/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:26:37 by ikotvits          #+#    #+#             */
/*   Updated: 2018/08/25 10:26:38 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
#define ABS(x) ((x) < 0) ? (-x) : (x)

typedef struct		s_map
{
	char			*str;
	struct s_map	*next;
}					t_map;

typedef struct		s_dot
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_dot;

typedef	struct		s_draw
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				dx;
	int				dy;
	int				err;
	int				e2;
}					t_draw;

typedef struct		s_fdf
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	double			x_shift;
	double			y_shift;
	int				*img;
	int				col;
	int				rows;
	t_dot			**dots;
	t_map			*map;
	t_draw			*draw;
	int				win_size;
	int				fd;
	double			zoom;
}					t_fdf;

#endif