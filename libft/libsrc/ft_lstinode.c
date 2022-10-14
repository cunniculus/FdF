/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:00:26 by guolivei          #+#    #+#             */
/*   Updated: 2022/10/14 16:01:13 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstinode(t_list *lst, int i)
{
	int	index;

	index = 0;
	while (lst)
	{
		if (index == i)
			return (lst);
		index++;
		lst = lst->next;
	}
	return (NULL);
}
