/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:25:10 by guolivei          #+#    #+#             */
/*   Updated: 2022/10/14 12:28:42 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* This function needs to exist, but it is useless for the moment */
int	handle_no_event(void *data)
{
	return (*((int *)data));
}

int	key_hook(int keycode, t_data *mlx)
{
	ft_printf("key %d pressed\n!", keycode);
	full_color_screen(*mlx, 0x0);
	if ((keycode >= L_ARROW && keycode <= D_ARROW) || keycode == LETTER_A || \
		keycode == LETTER_S)
	{
		mlx->transformed_map = generate_image(mlx, keycode);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	}
	else if (keycode == ESC)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(0);
	}
	return (0);
}

int	redraw_expose(t_data *vars)
{
	ft_printf("redraw ");
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img, 0, 0);
	return (0);
}
