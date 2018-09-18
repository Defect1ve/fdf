/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:35:10 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/31 16:11:25 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	out;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (dst)
		i = ft_strlen(dst);
	j = ft_strlen(src);
	if (size <= i)
		out = (size + j);
	else
		out = i + j;
	j = 0;
	while (j[src] != '\0' && i < (size - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (out);
}
