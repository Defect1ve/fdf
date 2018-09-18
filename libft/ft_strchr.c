/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:49:45 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/20 14:49:47 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *string, int symbol)
{
	char c;

	c = (char)symbol;
	while (string && *string != c)
	{
		if (!*string)
			return (0);
		string++;
	}
	return (char *)string;
}
