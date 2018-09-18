/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 20:49:13 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/20 20:49:14 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	a;
	size_t			i;
	unsigned char	*ptr;

	i = -1;
	a = (unsigned char)c;
	ptr = (unsigned char *)b;
	while (++i < len)
		ptr[i] = a;
	return (b);
}
