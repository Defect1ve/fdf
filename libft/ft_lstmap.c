/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:36:44 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/26 17:36:45 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*begin;

	if (!lst || !f)
		return (0);
	res = (t_list *)malloc(sizeof(t_list));
	res = f(lst);
	begin = res;
	while (lst->next)
	{
		lst = lst->next;
		if (!(res->next = f(lst)))
		{
			free(begin);
			return (0);
		}
		res = res->next;
	}
	return (begin);
}
