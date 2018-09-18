/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:45:21 by ikotvits          #+#    #+#             */
/*   Updated: 2018/05/09 14:45:22 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_buf_add_numb(t_pf *s, unsigned char symbol)
{
	if (s->i == BUFF_SIZE - 1)
		ft_buf_print(s);
	if (!symbol)
	{
		if (s->width > s->prec)
			s->i += s->width - s->prec;
		ft_strcpy(s->buf, (char *)N_STR);
		s->i += 6;
	}
	if (symbol)
	{
		s->width--;
		s->buf[s->i++] = symbol;
	}
}

void		ft_buf_add_str(t_pf *s, unsigned char *str)
{
	if (!str)
		str = (unsigned char *)N_STR;
	while (str && *str && s->prec > 0)
	{
		if (s->i == BUFF_SIZE - 1)
			ft_buf_print(s);
		s->buf[s->i++] = *str++;
		s->prec--;
		s->width--;
	}
}

void		ft_buf_print(t_pf *s)
{
	while (s->buf[s->i] != '\0' && s->i < BUFF_SIZE)
		s->i++;
	s->sum += s->i;
	write(1, s->buf, s->i);
	s->i = 0;
	ft_bzero(s->buf, BUFF_SIZE);
}

void		ft_buf_add_char(t_pf *s, unsigned char c)
{
	if (s->i == BUFF_SIZE - 1)
		ft_buf_print(s);
	s->buf[s->i++] = c;
	s->prec--;
	s->width--;
}

uintmax_t	ft_pow(uintmax_t b, uintmax_t p)
{
	if (p == 0)
		return (1);
	return (b * ft_pow(b, p - 1));
}
