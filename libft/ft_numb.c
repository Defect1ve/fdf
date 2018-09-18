/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 13:18:48 by ikotvits          #+#    #+#             */
/*   Updated: 2018/05/12 13:18:49 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_base_help(t_pf *s, uintmax_t p)
{
	while ((s->flags & 4 && s->width > (int)p && s->prec == -1 &&
	!(s->flags & 2)) || (s->prec > 0 && (uintmax_t)s->prec > p))
	{
		if (s->prec > 0)
			s->prec--;
		ft_buf_add_numb(s, '0');
	}
}

void		ft_s_base(t_pf *s, uintmax_t n, char *base)
{
	uintmax_t	b;
	uintmax_t	p;
	uintmax_t	copy;

	copy = n;
	p = 1;
	b = ft_strlen(base);
	while (n / ft_pow(b, p - 1) >= b)
		p++;
	if (!(s->flags & 2))
		ft_manage_numb(s, p, n);
	ft_mng_nb1(s, n);
	ft_base_help(s, p);
	while (p && !(s->prec == 0 && copy == 0))
	{
		ft_buf_add_numb(s, base[n / ft_pow(b, p - 1)]);
		n = n - n / ft_pow(b, p - 1) * ft_pow(b, p - 1);
		p--;
	}
	if (s->flags & 2)
		ft_manage_numb(s, p, n);
}

uintmax_t	ft_get_uint(t_pf *s, va_list val)
{
	if (s->type != 'p' && s->type != 'U' && s->type != 'O')
	{
		if (s->size[0] == '\0')
			return (va_arg(val, unsigned int));
		else if (ft_strcmp(s->size, "hh") == 0)
			return ((unsigned char)va_arg(val, int));
		else if (ft_strcmp(s->size, "h") == 0)
			return ((unsigned short int)va_arg(val, int));
	}
	return (va_arg(val, uintmax_t));
}

intmax_t	ft_get_int(t_pf *s, va_list val)
{
	intmax_t n;

	if (s->size[0] == 'l' || s->size[0] == 'j'
	|| s->size[0] == 'z' || s->type == 'D')
		n = va_arg(val, intmax_t);
	else if (s->size[0] == 'h' && s->size[1] == 'h')
		n = (char)va_arg(val, int);
	else if (s->size[0] == 'h')
		n = (short)va_arg(val, int);
	else
		n = va_arg(val, int);
	if (n < 0)
	{
		s->sign = '-';
		n *= -1;
	}
	return (n);
}

void		ft_numb(t_pf *s, va_list val)
{
	if (s->type == 'd' || s->type == 'D' || s->type == 'i')
		ft_s_base(s, ft_get_int(s, val), "0123456789");
	else if (s->type == 'X')
		ft_s_base(s, ft_get_uint(s, val), "0123456789ABCDEF");
	else if (s->type == 'p' || s->type == 'x')
		ft_s_base(s, ft_get_uint(s, val), "0123456789abcdef");
	else if (s->type == 'u' || s->type == 'U')
		ft_s_base(s, ft_get_uint(s, val), "0123456789");
	else if (s->type == 'O' || s->type == 'o')
		ft_s_base(s, ft_get_uint(s, val), "01234567");
}
