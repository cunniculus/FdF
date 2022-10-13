#include "fdf.h"

t_list  *scale(t_list *map, t_boundaries bound)
{
	t_list		*tmp;
	t_point		*point;

	if (bound.max_x)
	{
		;
	}
	tmp = NULL;
	while (map)	
	{
		point = malloc(sizeof (t_point));
		point->x = ((t_point *)map->content)->x * SCALE;
		point->y = ((t_point *)map->content)->y * SCALE;
		point->z = ((t_point *)map->content)->z * SCALE;
		ft_lstadd_back(&tmp, ft_lstnew(point));
		map = map->next;
	}	
	return (tmp);
}

void	init_scale_matrix(t_matrix  *scale, float x_range, float y_range)
{
	if (x_range &&y_range)
	{
		;
	}
	scale->r1[0] = 30;
	scale->r1[1] = 0;
	scale->r1[2] = 0;

	scale->r2[0] = 0;
	scale->r2[1] = 30;
	scale->r2[2] = 0;

	scale->r3[0] = 0;
	scale->r3[1] = 0;
	scale->r3[2] = 30;
}
