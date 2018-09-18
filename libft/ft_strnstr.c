/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:14:25 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/20 16:14:27 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*res;
	const char	*start;
	size_t		l;

	if (*needle == '\0')
		return (char *)haystack;
	start = needle;
	while (*haystack != '\0' && len > 0 && *haystack)
	{
		needle = start;
		res = haystack;
		l = len;
		while (*haystack == *needle && len > 0)
		{
			haystack++;
			needle++;
			if (*needle == '\0')
				return (char *)res;
			len--;
		}
		len = l;
		haystack = ++res;
		len--;
	}
	return (0);
}
