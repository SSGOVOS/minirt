/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:40:42 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/26 19:40:43 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*save;

	if (!lst || !del || !(*lst))
		return ;
	node = *lst;
	while (node)
	{
		del(node->content);
		save = node->next;
		free(node);
		node = save;
	}
	*lst = NULL;
}
