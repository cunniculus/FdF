/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:03:52 by guolive           #+#    #+#             */
/*   Updated: 2022/10/13 22:42:10 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*rotation(t_list *map, int keycode)
{
	t_list					*rotated;
	t_point					*point;
	static t_rotated_angle	angle;

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

t_rotated_angle	get_angle(t_rotated_angle angle, int keycode)
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

t_point	step_rotation(t_point point, t_rotated_angle angle)
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

t_point	transformation(t_matrix matrix, t_point point)
{
	t_point	transformed_point;

	transformed_point.x = dot_product(matrix.r1, point);
	transformed_point.y = dot_product(matrix.r2, point);
	transformed_point.z = dot_product(matrix.r3, point);
	return (transformed_point);
}

void	init_rot_matrix_x(t_matrix	*rotation, float degrees)
{
	float	angle;

	angle = 2 * M_PI * degrees / 360;
	rotation->r1[0] = 1;
	rotation->r1[1] = 0;
	rotation->r1[2] = 0;
	rotation->r2[0] = 0;
	rotation->r2[1] = cos(angle);
	rotation->r2[2] = -sin(angle);
	rotation->r3[0] = 0;
	rotation->r3[1] = -rotation->r2[2];
	rotation->r3[2] = rotation->r2[1];
}

void	init_rot_matrix_y(t_matrix	*rotation, float degrees)
{
	float	angle;

	angle = 2 * M_PI * degrees / 360;
	rotation->r1[0] = cos(angle);
	rotation->r1[1] = 0;
	rotation->r1[2] = sin(angle);
	rotation->r2[0] = 0;
	rotation->r2[1] = 1;
	rotation->r2[2] = 0;
	rotation->r3[0] = -rotation->r1[2];
	rotation->r3[1] = 0;
	rotation->r3[2] = rotation->r1[0];
}

void	init_rot_matrix_z(t_matrix	*rotation, float degrees)
{
	float	angle;

	angle = 2 * M_PI * degrees / 360;
	rotation->r1[0] = cos(angle);
	rotation->r1[1] = -sin(angle);
	rotation->r1[2] = 0;
	rotation->r2[0] = -rotation->r1[1];
	rotation->r2[1] = rotation->r1[0];
	rotation->r2[2] = 0;
	rotation->r3[0] = 0;
	rotation->r3[1] = 0;
	rotation->r3[2] = 1;
}

float	dot_product(float row[3], t_point point)
{
	float	dp;

	dp = row[0] * point.x + row[1] * point.y + row[2] * point.z;
	return (dp);
}
