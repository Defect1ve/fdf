/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:08:38 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/21 16:08:39 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	size_t			i;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (i < len)
	{
		if (dest < source)
			dest[i] = source[i];
		else
			dest[len - i - 1] = source[len - i - 1];
		i++;
	}
	return (dst);
}
