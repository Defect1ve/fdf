/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 16:57:01 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/26 16:57:02 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*next;

	if (!del || !alst || !*alst)
		return ;
	list = *alst;
	next = list;
	while ((list = next))
	{
		if (list->content)
			del(list->content, list->content_size);
		next = list->next;
		free(list);
	}
	*alst = 0;
}
