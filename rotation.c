/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:03:52 by guolive           #+#    #+#             */
/*   Updated: 2022/10/14 16:27:06 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*rotation(t_list *map, int keycode)
{
	t_list			*rotated;
	t_point			*point;
	static t_angle	angle;

	angle = get_angle (angle, keycode);
	rotated = NULL;
	point = NULL;
	while (map)
	{
		point = malloc(sizeof (t_point));
		*point = *((t_point *)map->content);
		if ((keycode >= L_ARROW && keycode <= D_ARROW) || \
			keycode == LETTER_A || keycode == LETTER_S)
			*point = step_rotation(*point, angle);
		else if (!keycode)
			*point = isometric_rotation(*point);
		ft_lstadd_back(&rotated, ft_lstnew(point));
		map = map->next;
	}
	return (rotated);
}

t_angle	get_angle(t_angle angle, int keycode)
{
	if (keycode == U_ARROW)
		angle.x = (angle.x + ROTATION_STEP) % 360;
	else if (keycode == D_ARROW)
		angle.x = (angle.x - ROTATION_STEP) % 360;
	else if (keycode == R_ARROW)
		angle.y = (angle.y + ROTATION_STEP) % 360;
	else if (keycode == L_ARROW)
		angle.y = (angle.y - ROTATION_STEP) % 360;
	else if (keycode == LETTER_A)
		angle.z = (angle.z + ROTATION_STEP) % 360;
	else if (keycode == LETTER_S)
		angle.z = (angle.z - ROTATION_STEP) % 360;
	return (angle);
}

t_point	isometric_rotation(t_point point)
{
	t_matrix		rotation;
	t_point			transformed_point;

	init_rot_matrix_z(&rotation, ISOMETRIC_Z_ANGLE);
	transformed_point = transformation(rotation, point);
	init_rot_matrix_x(&rotation, ISOMETRIC_X_ANGLE);
	transformed_point = transformation(rotation, transformed_point);
	return (transformed_point);
}

t_point	step_rotation(t_point point, t_angle angle)
{
	t_matrix	rotation;
	t_point		transformed_point;

	init_rot_matrix_x(&rotation, angle.x);
	transformed_point = transformation(rotation, point);
	init_rot_matrix_y(&rotation, angle.y);
	transformed_point = transformation(rotation, transformed_point);
	init_rot_matrix_z(&rotation, angle.z);
	transformed_point = transformation(rotation, transformed_point);
	return (transformed_point);
}
