/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:26:32 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/26 15:26:33 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (0);
	if (!content)
	{
		new->content = 0;
		new->content_size = 0;
		new->next = 0;
	}
	else
	{
		if (!(new->content = (void *)malloc(content_size)))
			return (0);
		ft_memcpy(new->content, (void *)content, content_size);
		new->content_size = content_size;
		new->next = 0;
	}
	return (new);
}
