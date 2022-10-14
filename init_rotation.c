/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:22:14 by guolivei          #+#    #+#             */
/*   Updated: 2022/10/14 16:22:16 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
