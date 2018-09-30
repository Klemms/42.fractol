/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 02:58:57 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 02:45:32 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"
#include <stdio.h>

void		mandelbrot_init(t_window *w)
{
	w->x1 = -2.1;
	w->x2 = 0.6;
	w->y1 = -1.2;
	w->y2 = 1.2;
	w->zoom_x = (w->width / (w->x2 - w->x1));
	w->zoom_y = (w->height / (w->y2 - w->y1));
	generate_colors(w);
	mandelbrot_render(w);
	render_iterations(w);
}

t_fractal	*mandelbrot_init_render(t_window *w)
{
	t_fractal	*fractal;

	if ((fractal = malloc(sizeof(t_fractal))) == NULL)
		handle_error(ERR_MEMORY, 1);
	fractal->c_r = 0;
	fractal->c_i = 0;
	fractal->z_r = 0;
	fractal->z_i = 0;
	fractal->tmp = 0;
	fractal->i = 0;
	return (fractal);
}

void	mandelbrot_render(t_window *w)
{
	long double	x;
	long double	y;
	long double size;
	long double smoothed;
	int			k;
	t_fractal	*fl;

	make_screen(w);
	mlx_put_image_to_window(w->mlx, w->window, w->img_screen, 0, 0);
	y = 0;
	k = 0;
	fl = mandelbrot_init_render(w);
	while (y < w->height)
	{
		x = 0;
		while (x < w->width)
		{
			fl->c_r = w->x1 + (x * (w->x2 - w->x1)) / w->width;
			fl->c_i = w->y1 + (y * (w->y2 - w->y1)) / w->height;
			fl->z_r = 0;
			fl->z_i = 0;
			fl->i = 0;
			fl->tmp = fl->z_r;
			fl->z_r = fl->z_r * fl->z_r - fl->z_i * fl->z_i + fl->c_r;
			fl->z_i = (fl->z_i + fl->z_i ) * fl->tmp + fl->c_i;
			while ((fl->z_r * fl->z_r + fl->z_i * fl->z_i) < 4 && fl->i < w->max_iteration - 1)
			{
				fl->tmp = fl->z_r;
				fl->z_r = fl->z_r * fl->z_r - fl->z_i * fl->z_i + fl->c_r;
				fl->z_i = (fl->z_i + fl->z_i ) * fl->tmp + fl->c_i;
				fl->i++;
			}
			w->img_pixels[k] = w->colors[fl->i];
			x++;
			k++;
		}
		y++;
	}
	fflush(stdout);
	mlx_put_image_to_window(w->mlx, w->window, w->img_screen, 0, 0);
	destroy_image(w);
	free(fl);
}
