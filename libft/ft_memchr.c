/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:49:09 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/21 17:49:11 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	a;
	size_t			i;
	unsigned char	*ptr;

	i = -1;
	a = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (++i < n)
		if (ptr[i] == a)
			return (ptr + i);
	return (0);
}
