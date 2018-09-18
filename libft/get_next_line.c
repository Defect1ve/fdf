/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 13:55:50 by ikotvits          #+#    #+#             */
/*   Updated: 2018/04/18 13:56:01 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		help(t_gnl *s, char **line)
{
	if ((s->p = ft_strchr(s->b, '\n')))
		*(s->p) = '\0';
	*line = ft_strjoinfree(line, s->b);
	if (s->p)
	{
		if (!(*line))
			*line = ft_strdup("");
		ft_memmove(s->b, s->p + 1, ft_strlen(s->p + 1) + 1);
		return (1);
	}
	ft_bzero(s->b, BUFF + 1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl *s;

	if (!s)
	{
		if (!(s = (t_gnl *)malloc(sizeof(t_gnl))))
			return (-1);
		ft_bzero(s->b, BUFF + 1);
	}
	if (fd < 0 || read(fd, 0, 0) < 0 || !line || fd > 256)
		return (-1);
	*line = NULL;
	if (help(s, line))
		return (1);
	while (read(fd, s->b, BUFF))
	{
		if (help(s, line))
			return (1);
		else
			ft_bzero(s->b, BUFF + 1);
	}
	if (!(*line))
		return (0);
	return (1);
}
