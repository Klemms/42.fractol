/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 02:58:57 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 07:34:17 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void		ship_init(t_window *w)
{
	w->x1 = -1.85;
	w->x2 = -1.65;
	w->y1 = -0.1;
	w->y2 = 0.1;
	w->zoom_x = (w->width / (w->x2 - w->x1));
	w->zoom_y = (w->height / (w->y2 - w->y1));
	generate_colors(w);
	ship_render(w);
	render_iterations(w);
}

t_fractal	*ship_init_render()
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

void	ship_render(t_window *w)
{
	long double	x;
	long double	y;
	int			k;
	t_fractal	*fl;

	make_screen(w);
	mlx_put_image_to_window(w->mlx, w->window, w->img_screen, 0, 0);
	y = w->height - 1;
	k = 0;
	fl = ship_init_render();
	while (y >= 0)
	{
		x = 0;
		while (x < w->width)
		{
			fl->c_r = w->x1 + (x * (w->x2 - w->x1)) / w->width;
			fl->c_i = w->y1 + (y * (w->y2 - w->y1)) / w->height;
			fl->z_r = 0;
			fl->z_i = 0;
			fl->i = 0;
			fl->tmp = fl->z_i;
			fl->z_i = fabsl(fl->z_r * fl->z_i);
			fl->z_i = fl->z_i + fl->z_i - fl->c_i;
			fl->z_r = fl->z_r * fl->z_r - fl->tmp * fl->tmp + fl->c_r;
			while ((fl->z_r * fl->z_r + fl->z_i * fl->z_i) < 4 && fl->i < w->max_iteration - 1)
			{
				fl->tmp = fl->z_i;
				fl->z_i = fabsl(fl->z_r * fl->z_i);
				fl->z_i = fl->z_i + fl->z_i - fl->c_i;
				fl->z_r = fl->z_r * fl->z_r - fl->tmp * fl->tmp + fl->c_r;
				fl->i++;
			}
			w->img_pixels[k] = w->colors[fl->i];
			x++;
			k++;
		}
		y--;
	}
	mlx_put_image_to_window(w->mlx, w->window, w->img_screen, 0, 0);
	destroy_image(w);
	free(fl);
}
