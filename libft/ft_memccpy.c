/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 15:15:03 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/21 15:15:04 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*source;
	size_t			i;
	unsigned char	*dest;
	unsigned char	ch;

	i = -1;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	ch = (unsigned char)c;
	while (++i < n)
	{
		dest[i] = source[i];
		if (source[i] == ch)
			return (dest + i + 1);
	}
	return (0);
}
