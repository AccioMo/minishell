/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:15:59 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/12 16:04:42 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),	void (*del)(void *))
{
	t_list	*anchor;
	t_list	*final;
	void	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	anchor = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		final = ft_lstnew(tmp);
		if (!final)
		{
			del(tmp);
			ft_lstclear(&anchor, del);
			return (NULL);
		}
		ft_lstadd_back(&anchor, final);
		lst = lst->next;
	}
	return (anchor);
}
