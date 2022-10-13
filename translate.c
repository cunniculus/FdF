#include "fdf.h"

t_list	*translate(t_list *map)
{
    t_matrix    transl;
	t_list		*tmp;

    init_transl_matrix(&transl);
	tmp = map;
	while (tmp)	
	{
		((t_point *)tmp->content)->x = ((t_point *)tmp->content)->x + 200;
		((t_point *)tmp->content)->y = ((t_point *)tmp->content)->y + 200;
		tmp = tmp->next;
	}	
	return (map);
}


void	init_transl_matrix(t_matrix	*matrix)
{
	matrix->r1[0] = 1;
	matrix->r1[1] = 0;
	matrix->r1[2] = 90;

	matrix->r2[0] = 0;
	matrix->r2[1] = 1;
	matrix->r2[2] = 80;

	matrix->r3[0] = 0;
	matrix->r3[1] = 0;
	matrix->r3[2] = 1;
}

t_boundaries	map_boundaries(t_list *list)
{
	t_boundaries	bound;

	max_coord(list, &bound);
	min_coord(list, &bound);
	return (bound);
}


t_boundaries	max_coord(t_list *list, t_boundaries *bound)
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
			bound->max_z = ((t_point*)list->content)->z;
		list = list->next;
	}
	return (*bound);
}

t_boundaries	min_coord(t_list *list, t_boundaries *bound)
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
