/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 20:08:37 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/26 20:08:38 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoinfree(char **s1, char *s2)
{
	char			*p;
	char			*b;
	unsigned long	len;
	unsigned long	i;

	if (!s1 && !s2)
		return (0);
	len = ft_strlen(*s1) + ft_strlen(s2);
	p = (len) ? ft_strnew(len) : NULL;
	b = p;
	if (!p)
		return (0);
	i = 0;
	while (s1 && *s1 && *(*s1 + i))
		*p++ = *(*s1 + i++);
	i = 0;
	while (*(s2 + i))
		*p++ = *(s2 + i++);
	if (s1 && *s1)
		ft_strdel(s1);
	return (b);
}
