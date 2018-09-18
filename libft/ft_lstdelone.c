/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 16:41:25 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/26 16:41:27 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;

	if (!alst || !(*alst) || !del)
		return ;
	list = *alst;
	if (list)
	{
		if (list->content)
			del(list->content, list->content_size);
		free(list);
	}
	*alst = 0;
}
