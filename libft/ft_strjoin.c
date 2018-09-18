/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 17:45:06 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/22 17:45:07 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s1 && s1[i] != 0)
		i++;
	j = 0;
	while (s2 && s2[j] != 0)
		j++;
	if ((!s1 && !s2) || !(str = (char *)malloc(i + j + 1)))
		return (0);
	if (s1)
		i = -1;
	else
		i = 0;
	while (s1 && s1[++i])
		str[i] = s1[i];
	str[i + j] = '\0';
	while (s2 && s2[--j])
		str[i + j] = s2[j];
	return (str);
}
