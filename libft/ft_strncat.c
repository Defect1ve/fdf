/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:10:04 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/20 14:10:05 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *destptr, char *srcptr, size_t num)
{
	int		i;
	size_t	j;

	i = 0;
	while (destptr[i] != '\0')
		i++;
	j = 0;
	while (srcptr[j] != '\0' && j < num)
		destptr[i++] = srcptr[j++];
	destptr[i] = '\0';
	return (destptr);
}
