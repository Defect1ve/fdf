/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 12:05:55 by ikotvits          #+#    #+#             */
/*   Updated: 2018/05/17 12:05:56 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_manage_str(t_pf *s, int l)
{
	int len;

	if (l > s->prec)
		l = s->prec;
	len = s->width - l;
	if (len != 0)
		while (len-- > 0)
		{
			if (s->i == BUFF_SIZE - 1)
				ft_buf_print(s);
			if (s->flags & 4 && (!(s->flags & 2)))
				s->buf[s->i++] = '0';
			else
				s->buf[s->i++] = ' ';
		}
}

void	ft_mng_nb1(t_pf *s, uintmax_t n)
{
	if (s->flags & 16 && (s->type == 'd' || s->type == 'D' || s->type == 'i')
	&& !(s->flags & 1) && (s->sign != '-'))
		ft_buf_add_numb(s, ' ');
	if ((s->type == 'd' || s->type == 'D' || s->type == 'i') && (s->sign == '-'
	|| (s->flags & 1)))
		ft_buf_add_numb(s, s->sign);
	if ((s->flags & 8 && (n != 0 || ((s->type == 'o' || s->type == 'O')
	&& s->prec != -1))) || s->type == 'p')
	{
		if (s->type == 'o' || s->type == 'O')
		{
			ft_buf_add_numb(s, '0');
			if (s->prec > 0)
				s->prec--;
		}
		if (s->type == 'x' || s->type == 'X' || s->type == 'p')
			ft_buf_add_numb(s, '0');
		if (s->type == 'x' || s->type == 'p')
			ft_buf_add_numb(s, 'x');
		if (s->type == 'X')
			ft_buf_add_numb(s, 'X');
	}
}

void	ft_spaces(int w, t_pf *s, uintmax_t b)
{
	if (w != 0 && (!(s->flags & 4) || s->flags & 2 ||
	(s->flags & 4 && s->prec != -1)) && w > (int)b)
		while (w-- - b > 0)
		{
			if (s->i == BUFF_SIZE - 1)
				ft_buf_print(s);
			s->buf[s->i++] = ' ';
		}
}

int		ft_manage_help(int w, t_pf *s, uintmax_t b, uintmax_t n)
{
	if ((!(s->flags & 2)) && s->width != 0 &&
	(!(s->flags & 4) || s->prec != -1))
	{
		if (s->flags & 16 && (s->type == 'd' || s->type == 'D' ||
		s->type == 'i') && !(s->flags & 1) && (s->sign != '-'))
			w--;
		if (s->flags & 8 && (s->type == 'o' || s->type == 'O') && n != 0)
		{
			if (s->prec <= (int)b)
				w--;
		}
		if ((s->flags & 8 && (s->type == 'x' || s->type == 'X') && n != 0)
		|| s->type == 'p')
			w -= 2;
		if (s->prec != -1 && s->prec > (int)b)
			w -= s->prec - b;
	}
	return (w);
}

void	ft_manage_numb(t_pf *s, uintmax_t b, uintmax_t n)
{
	int w;

	w = s->width;
	if (n == 0 && s->prec == 0)
		b = 0;
	if ((s->type == 'd' || s->type == 'D' || s->type == 'i') && (s->sign == '-'
	|| (s->flags & 1)) && !(s->flags & 2))
		w--;
	w = ft_manage_help(w, s, b, n);
	ft_spaces(w, s, b);
}
