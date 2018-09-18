/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:38:45 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/31 16:06:02 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int symbol)
{
	char *help;
	char s;

	s = (char)symbol;
	help = (char *)string;
	while (*help)
		help++;
	while (help >= string && *help != s)
	{
		help--;
		if (!(*help) || help < string)
			return (0);
	}
	return ((char *)(help));
}
