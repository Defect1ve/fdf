/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:00:42 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/20 16:00:43 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *string1, const char *string2)
{
	const char	*res;
	const char	*start;

	if (*string2 == '\0')
		return (char *)string1;
	while (*string1)
	{
		start = string2;
		res = string1;
		while (*string1 == *string2)
		{
			string1++;
			string2++;
			if (*string2 == '\0')
				return (char *)res;
		}
		string2 = start;
		string1 = ++res;
	}
	return (0);
}
