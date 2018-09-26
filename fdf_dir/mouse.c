/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 16:07:28 by ikotvits          #+#    #+#             */
/*   Updated: 2018/09/26 16:07:30 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			mouse_press(int button, int x, int y, t_fdf *fdf)
{
	if (button == 5)
		fdf->zoom /= 1.1;
	else if (button == 4)
		fdf->zoom *= 1.1;
	else if (button == 1)
		fdf->mouse.pressed = 1;
	redraw(fdf);
	x = y;
	return (0);
}

int			mouse_release(int button, int x, int y, t_fdf *fdf)
{
	fdf->mouse.pressed = 0;
	x = y;
	return (0);
}

int			mouse_move(int x, int y, t_fdf *fdf)
{
	if (fdf->mouse.pressed == 1)
		fdf->mouse.pressed = 2;
	else if (fdf->mouse.pressed == 2)
	{
		y_rotate(fdf, (double)(fdf->mouse.x - x) / 300);
		x_rotate(fdf, (double)(fdf->mouse.y - y) / 300);
		redraw(fdf);
	}
	fdf->mouse.x = x;
	fdf->mouse.y = y;
	return (0);
}
