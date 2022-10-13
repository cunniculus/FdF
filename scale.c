#include "fdf.h"

t_list  *scale(t_list *map, t_boundaries bound)
{
    float       x_range;
    float       y_range;
    t_matrix    scale;
	t_list		*tmp;
	t_point		*point;

    x_range = bound.max_x - bound.min_x;
    y_range = bound.max_y - bound.min_y;
    init_scale_matrix(&scale, x_range, y_range);
	tmp = NULL;
	while (map)	
	{
		point = malloc(sizeof (t_point));
		*point = transformation(scale, map->content);
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
