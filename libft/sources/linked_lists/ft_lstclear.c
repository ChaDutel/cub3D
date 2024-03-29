/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:36:38 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 18:56:55 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*previous;
	t_list	*elem;

	if (!*lst)
		return ;
	elem = *lst;
	while (elem != 0)
	{
		previous = elem;
		elem = elem->next;
		(*del)(previous->content);
		free(previous);
	}
	*lst = NULL;
}
