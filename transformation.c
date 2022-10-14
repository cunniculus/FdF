/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:25:50 by guolivei          #+#    #+#             */
/*   Updated: 2022/10/14 16:26:24 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	transformation(t_matrix matrix, t_point point)
{
	t_point	transformed_point;

	transformed_point.x = dot_product(matrix.r1, point);
	transformed_point.y = dot_product(matrix.r2, point);
	transformed_point.z = dot_product(matrix.r3, point);
	return (transformed_point);
}

float	dot_product(float row[3], t_point point)
{
	float	dp;

	dp = row[0] * point.x + row[1] * point.y + row[2] * point.z;
	return (dp);
}
