/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 02:58:57 by cababou           #+#    #+#             */
/*   Updated: 2018/09/30 15:18:17 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

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

t_fractal	*mandelbrot_init_render()
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
	fractal->k = 0;
	return (fractal);
}

void		m_r_2(t_window *w, long double *x, long double *y, t_fractal *fl)
{
	while ((*x) < w->width)
	{
		fl->c_r = w->x1 + ((*x) * (w->x2 - w->x1)) / w->width;
		fl->c_i = w->y1 + ((*y) * (w->y2 - w->y1)) / w->height;
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
		w->img_pixels[fl->k] = w->colors[fl->i];
		(*x)++;
		fl->k++;
	}
}

void	mandelbrot_render(t_window *w)
{
	long double	x;
	long double	y;
	t_fractal	*fl;

	make_screen(w);
	mlx_put_image_to_window(w->mlx, w->window, w->img_screen, 0, 0);
	y = 0;
	fl = mandelbrot_init_render();
	while (y < w->height)
	{
		x = 0;
		m_r_2(w, &x, &y, fl);
		y++;
	}
	mlx_put_image_to_window(w->mlx, w->window, w->img_screen, 0, 0);
	destroy_image(w);
	free(fl);
}
