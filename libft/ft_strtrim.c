/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 18:05:15 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/22 18:05:18 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	if (!s)
		return (0);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	if (s && *s == '\0')
		return (ft_strdup(""));
	while (s && s[len])
		len++;
	len--;
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
		len--;
	if (!(str = (char *)malloc(len + 2)))
		return (0);
	i = 0;
	while (len-- >= 0)
		str[i++] = *(s++);
	str[i] = '\0';
	return (str);
}
