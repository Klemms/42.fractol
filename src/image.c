/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 06:12:44 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 00:08:27 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	make_screen(t_window *w)
{
	if ((w->img_screen = mlx_new_image(w->mlx, w->width, w->height)) == NULL)
		handle_error(ERR_MEMORY, 1);
	w->img_pixels = (int *)mlx_get_data_addr(w->img_screen,
		&w->img_bits_per_pixel, &w->img_size_line, &w->img_endian);
}

void	destroy_image(t_window *w)
{
	mlx_destroy_image(w->mlx, w->img_screen);
}
