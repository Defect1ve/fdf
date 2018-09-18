/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstbackadd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:52:43 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/26 17:52:44 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstbackadd(t_list **alst, t_list *new)
{
	t_list	*list;
	t_list	*add;

	if (!alst || !(*alst))
		return ;
	list = *alst;
	if (list && new)
	{
		while (list->next)
			list = list->next;
		add = new;
		list->next = add;
	}
}
