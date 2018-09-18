/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 18:58:46 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/31 17:15:09 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		words(char const *s, char c)
{
	int i;
	int t;
	int check;

	i = 0;
	t = 0;
	check = 0;
	while (s && s[t] != '\0')
	{
		if (s[t] == c && check)
			check = 0;
		else if (s[t] != c && !check)
		{
			check = 1;
			i++;
		}
		t++;
	}
	return (i + 1);
}

static int		letters(char const *s, char c)
{
	int i;

	i = 0;
	while (s && *s && *(s++) != c)
		i++;
	return (i + 1);
}

static	int		ft_free(char **mass)
{
	while (*mass)
	{
		free(*mass);
		mass++;
	}
	free(mass);
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	char **mass;
	char *test;
	char **tes;

	if (!s || (!(mass = (char **)malloc(sizeof(char *) * words(s, c)))))
		return (0);
	tes = mass;
	while (s && *s)
	{
		while (s && *s == c)
			s++;
		if (s && (!*s))
			break ;
		if (!(*mass = (char *)malloc(letters(s, c))) && ft_free(tes))
			return (0);
		test = *mass;
		while (s && *s && *s != c)
			*(*mass)++ = *(s++);
		**mass = '\0';
		*mass = test;
		mass++;
	}
	*mass = 0;
	return (tes);
}
