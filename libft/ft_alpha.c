/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alpha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:22:46 by ikotvits          #+#    #+#             */
/*   Updated: 2018/05/03 15:22:47 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_unicode(t_pf *s, int uni)
{
	unsigned char mass[5];

	ft_bzero(mass, 5);
	if (uni < 128)
		mass[0] = uni;
	else if (uni < 2048)
	{
		mass[1] = 128 | (uni % 64);
		mass[0] = 192 | (uni / 64);
	}
	else if (uni < 65536)
	{
		mass[2] = 128 | (uni % 64);
		mass[1] = 128 | (uni % 4096 / 64);
		mass[0] = 224 | (uni / 4096);
	}
	else if (uni < 1114113)
	{
		mass[3] = 128 | (uni % 64);
		mass[2] = 128 | (uni % 4096 / 64);
		mass[1] = 128 | (uni % 524288 / 4096);
		mass[0] = 240 | (uni / 524288);
	}
	ft_buf_add_str(s, mass);
}

int				ft_str_len(int *c, t_pf *s, char type)
{
	int sum;

	sum = 0;
	if (!c)
		return (6);
	while (c && *c)
	{
		if (*c < 128 && (sum + 1 <= s->prec || s->prec == -1))
			sum += 1;
		else if (*c < 2048 && (sum + 2 <= s->prec || s->prec == -1))
			sum += 2;
		else if (*c < 65536 && (sum + 3 <= s->prec || s->prec == -1))
			sum += 3;
		else if (*c < 1114113 && (sum + 4 <= s->prec || s->prec == -1))
			sum += 4;
		else
			break ;
		if (type == 'c' || type == 'C')
			break ;
		c++;
	}
	return (sum);
}

void			ft_long_string(t_pf *s, wchar_t *c)
{
	size_t			len;

	len = ft_str_len(c, s, 's');
	if (s->prec == -1)
		s->prec = (c) ? len : 6;
	if (!(s->flags & 2))
		ft_manage_str(s, len);
	if (!c)
		ft_buf_add_str(s, NULL);
	while (c && *c && s->prec > 0)
	{
		if (*c > 256 && MB_CUR_MAX <= 1)
		{
			s->sum = -1;
			return ;
		}
		if (SIZE((int)*c) <= s->prec)
			ft_unicode(s, *c);
		else
			break ;
		c++;
	}
	if (s->flags & 2)
		ft_manage_str(s, 0);
}

void			ft_string(t_pf *s, va_list val)
{
	unsigned char	*str;
	size_t			len;
	wchar_t			*c;

	len = 6;
	if (s->type == 'S' || (s->type == 's' && s->size[0] == 'l'))
	{
		c = va_arg(val, wchar_t *);
		ft_long_string(s, c);
	}
	else if (s->type == 's')
	{
		if ((str = va_arg(val, unsigned char *)))
			len = ft_strlen((char *)str);
		if (s->prec == -1 && str)
			s->prec = len;
		if (s->prec == -1 && !str)
			s->prec = 6;
		if (!(s->flags & 2))
			ft_manage_str(s, len);
		ft_buf_add_str(s, str);
		if (s->flags & 2)
			ft_manage_str(s, 0);
	}
}

void			ft_char(t_pf *s, va_list val)
{
	wchar_t			c;
	int				len;

	len = 1;
	c = va_arg(val, wchar_t);
	if (s->type == 'C' || (s->type == 'c' && s->size[0] == 'l'))
	{
		s->prec = (MB_CUR_MAX > 1) ? 4 : 1;
		len = LEN(c);
	}
	if (s->prec < 1 && s->type == 'c' && s->size[0] != 'l')
		s->prec = len;
	if (!(s->flags & 2))
		ft_manage_str(s, len);
	if (MB_CUR_MAX > 1 && c > 0 && (s->type == 'C' || s->size[0] == 'l'))
		ft_unicode(s, c);
	else if ((c >= 0 && c <= 256) || s->type == 'c')
		ft_buf_add_char(s, c);
	else
	{
		s->sum = -1;
		return ;
	}
	if (s->flags & 2)
		ft_manage_str(s, 0);
}
