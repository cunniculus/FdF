/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:06:50 by guolive           #+#    #+#             */
/*   Updated: 2022/10/14 16:27:00 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*translate(t_list *map)
{
	t_point		*point;
	t_list		*translated;
	t_list		*tmp;

	translated = NULL;
	tmp = map;
	while (tmp)
	{
		point = malloc(sizeof (t_point));
		point->x = ((t_point *)tmp->content)->x + TRANSLATION_X;
		point->y = ((t_point *)tmp->content)->y + TRANSLATION_Y;
		point->z = ((t_point *)tmp->content)->z;
		ft_lstadd_back(&translated, ft_lstnew(point));
		tmp = tmp->next;
	}
	ft_lstclear(&map, free);
	return (translated);
}

t_ext	map_boundaries(t_list *list)
{
	t_ext	bound;

	max_coord(list, &bound);
	min_coord(list, &bound);
	return (bound);
}

t_ext	max_coord(t_list *list, t_ext *bound)
{
	bound->max_x = (float) INT_MIN;
	bound->max_y = (float) INT_MIN;
	bound->max_z = (float) INT_MIN;
	while (list)
	{
		if (((t_point *)list->content)->x > bound->max_x)
			bound->max_x = ((t_point *)list->content)->x;
		if (((t_point *)list->content)->y > bound->max_y)
			bound->max_y = ((t_point *)list->content)->y;
		if (((t_point *)list->content)->z > bound->max_z)
			bound->max_z = ((t_point *)list->content)->z;
		list = list->next;
	}
	return (*bound);
}

t_ext	min_coord(t_list *list, t_ext *bound)
{
	bound->min_x = (float) INT_MAX;
	bound->min_y = (float) INT_MAX;
	bound->min_z = (float) INT_MAX;
	while (list)
	{
		if (((t_point *)list->content)->x < bound->min_x)
			bound->min_x = ((t_point *)list->content)->x;
		if (((t_point *)list->content)->y < bound->min_y)
			bound->min_y = ((t_point *)list->content)->y;
		if (((t_point *)list->content)->z < bound->min_z)
			bound->min_z = ((t_point *)list->content)->z;
		list = list->next;
	}
	return (*bound);
}
