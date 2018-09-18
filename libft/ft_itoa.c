/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:00:43 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/21 19:00:44 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		tmp;

	len = 0;
	tmp = n;
	while ((tmp /= 10) != 0)
		len++;
	if (n < 0)
		len++;
	if (!(str = ft_memalloc(sizeof(char) * (len + 2))))
		return (0);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0 && (n = -n))
		str[0] = '-';
	str[len + 1] = '\0';
	while (len >= 0 && str[len] != '-')
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
