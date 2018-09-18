/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:05:14 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/20 13:05:17 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *destptr, const char *srcptr)
{
	int i;
	int j;

	i = 0;
	while (destptr[i] != '\0')
		i++;
	j = 0;
	while (srcptr[j] != '\0')
		destptr[i++] = srcptr[j++];
	destptr[i] = '\0';
	return (destptr);
}
