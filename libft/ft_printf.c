/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:03:19 by ikotvits          #+#    #+#             */
/*   Updated: 2018/05/02 17:03:20 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_flags(t_pf *s, char **f)
{
	s->flags = 0;
	s->sign = '+';
	while (**f == '+' || **f == '-' || **f == '0' || **f == '#' || **f == ' ')
	{
		if (**f == '+')
			s->flags = s->flags | 1;
		if (**f == '-')
			s->flags = s->flags | 2;
		if (**f == '0')
			s->flags = s->flags | 4;
		if (**f == '#')
			s->flags = s->flags | 8;
		if (**f == ' ')
			s->flags = s->flags | 16;
		(*f)++;
	}
}

void	ft_width(char **str, va_list val, t_pf *s)
{
	s->prec = -1;
	s->type = 0;
	s->width = 0;
	while ((**str > 47 && **str < 58) || **str == '*')
	{
		if (**str > 47 && **str < 58)
			s->width = ft_atoi(*str);
		while (**str > 47 && **str < 58)
			(*str)++;
		if (**str == '*')
		{
			s->width = va_arg(val, int);
			if (s->width < 0 && (s->width *= -1))
				s->flags = s->flags | 2;
			(*str)++;
		}
	}
}

void	handle_it(t_pf *s, va_list val)
{
	if (s->prec != -1 && s->prec < 0)
		s->prec = -1;
	if (s->type == 's' || s->type == 'S')
		ft_string(s, val);
	else if (s->type == 'c' || s->type == 'C')
		ft_char(s, val);
	else if (s->type == 'd' || s->type == 'D' || s->type == 'i' ||
	s->type == 'o' || s->type == 'O' || s->type == 'u' || s->type == 'U'
	|| s->type == 'p' || s->type == 'x' || s->type == 'X')
		ft_numb(s, val);
	else if (s->type)
	{
		if (s->prec == -1 || s->prec == 0)
			s->prec = 1;
		if (!(s->flags & 2))
			ft_manage_str(s, 1);
		s->buf[s->i++] = s->type;
		if (s->flags & 2)
			ft_manage_str(s, 1);
	}
}

void	parse_it(char **str, va_list val, t_pf *s)
{
	(*str)++;
	ft_bzero(s->size, sizeof(s->size));
	ft_flags(s, str);
	ft_width(str, val, s);
	if (**str == '.' && (*str)++)
	{
		s->prec = 0;
		while ((**str > 47 && **str < 58) || **str == '*')
		{
			s->prec = ft_atoi(*str);
			if (**str == '*')
				s->prec = va_arg(val, int);
			(*str)++;
			while (**str > 47 && **str < 58)
				(*str)++;
		}
	}
	if (**str == 'h' || **str == 'l' || **str == 'j' || **str == 'z')
		s->size[0] = *(*str)++;
	if (**str == 'h' || **str == 'l')
		s->size[1] = *(*str)++;
	if (*(*str))
		s->type = *(*str)++;
	handle_it(s, val);
}

int		ft_printf(const char *format, ...)
{
	va_list	val;
	t_pf	*s;

	va_start(val, format);
	s = (t_pf *)malloc(sizeof(t_pf));
	ft_bzero(s->buf, BUFF_SIZE);
	s->i = 0;
	s->sum = 0;
	while (format && *format)
	{
		while (*format && *format != '%')
			ft_buf_add_char(s, *(format)++);
		if (*format == '%')
			parse_it((char **)&format, val, s);
		if (s->sum == -1)
		{
			free(s);
			return (s->sum);
		}
	}
	ft_buf_print(s);
	free(s);
	va_end(val);
	return (s->sum);
}
